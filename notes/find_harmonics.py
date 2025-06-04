import os
import numpy as np
import scipy.signal
import librosa
import re
import argparse
import shutil
from enum import Enum

NOTE_NAMES = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B']
FLAT_TO_SHARP = {"Db": "C#", "Eb": "D#", "Gb": "F#", "Ab": "G#", "Bb": "A#"}

INIT_GAIN = 0
GAIN_LINES = ["", "gain = hslider(\"gain\", " + str(INIT_GAIN) +", 0, 1, 0.01);", ""]

TEST_FILE = ["declare options \"[osc:on]\";", "declare options \"[osc:on]\";", "import(\"stdfaust.lib\");", "process = no.noise*hslider(\"level\",0.02,0,1,0.01);"]

class ControllerType(str, Enum):
    BUTTON = "button"
    HSLIDER = "hslider"


def normalize_note(note):
    for flat, sharp in FLAT_TO_SHARP.items():
        if note.startswith(flat):
            return note.replace(flat, sharp)
    return note

def note_to_freq(note):
    note = normalize_note(note)
    match = re.match(r"([A-G]#?)(\d)", note)
    if not match:
        raise ValueError(f"Nota inválida: {note}")
    name, octave = match.groups()
    octave = int(octave)
    index = NOTE_NAMES.index(name)
    midi_num = 12 * (octave + 1) + index
    return 440.0 * 2 ** ((midi_num - 69) / 12)

def generate_harmonic_bank(n_harmonics):
    args = ", ".join([f"g{i}" for i in range(1, n_harmonics + 1)])
    body = " + \n    ".join([f"os.osc({i}*f) * g{i}" for i in range(1, n_harmonics + 1)])
    function_code = f"""harmonicBank(f, {args}) = 
    {body};"""
    return function_code

def find_harmonics(file_path, freq, harmonics_number):
    y, sr = librosa.load(file_path, sr=None, mono=True)
    start = len(y) // 2 - sr // 4
    end = start + sr // 2
    y_seg = y[start:end]
    window = np.hanning(len(y_seg))
    Y = np.abs(np.fft.rfft(y_seg * window))
    freqs = np.fft.rfftfreq(len(y_seg), 1 / sr)
    peaks, _ = scipy.signal.find_peaks(Y, height=0.01, distance=20)
    peak_freqs = freqs[peaks]
    peak_amps = Y[peaks]

    harmonics = []
    for i in range(1, harmonics_number+1):
        expected = i * freq
        idx = np.argmin(np.abs(peak_freqs - expected))
        harmonics.append((peak_freqs[idx], peak_amps[idx]))

    max_amp = max(a for _, a in harmonics)
    harmonics = [(m, a / max_amp) for m, a in harmonics]

    for i, (m, a) in enumerate(harmonics, 1):
        print(f"  H{i}: {m:.1f} Hz, {a:.3f}")

    return harmonics

def organize_notes_info(files):
    notes = {}

    for filename in files:
        if not filename.lower().endswith(".aif"):
            continue

        match = re.search(r"\.([A-Ga-g][b#]?\d)\.", filename)
        if not match:
            print(f"No se encontró nota en: {filename}")
            continue

        note = match.group(1)
        try:
            freq = note_to_freq(note)
            notes[round(freq, 2)] = (note, filename)
        except ValueError as e:
            print(f"Error al convertir nota: {e}")
            continue
    return dict(sorted(notes.items()))

def generate_files(args):
    harmonics_number = args.n
    controller = args.type

    init_lines = ["import(\"stdfaust.lib\");", "", generate_harmonic_bank(harmonics_number), "\n"]
    notes_lines = []
    harmonic_functions = []
    note_mix_lines = []
    note_funcs = []
    
    base_dir = os.path.dirname(os.path.abspath(__file__))
    notes_dir = os.path.join(base_dir, "sax_notes")
    notes_faust_dir = os.path.join(base_dir, "sax_single_notes_faust")
    scripts_dir = os.path.join(base_dir, "sax_full_faust")
    test_dir = os.path.join(base_dir, "test_noise")
    os.makedirs(notes_faust_dir, exist_ok=True)
    os.makedirs(scripts_dir, exist_ok=True)
    os.makedirs(test_dir, exist_ok=True)

    files = os.listdir(notes_dir)
    notes = organize_notes_info(files)
    
    for num, (freq, (note, filename)) in enumerate(notes.items()):

        print(f"\n{filename} (nota: {note}, f0 ≈ {freq:.2f} Hz)")

        note_std = normalize_note(note).replace('#', 's')
        func_name = f"harmonics_{note_std}"
        note_funcs.append(func_name)

        harmonics = find_harmonics(os.path.join(notes_dir, filename), freq, harmonics_number)

        faust_expr = ", ".join([f"{a:.3f}" for _, a in harmonics])
        harmonic_functions = f"{func_name} = harmonicBank({freq:.2f}, {faust_expr});"
        id = f"{(num+1):0{len(str(len(files)+1))}d}"

        if controller == ControllerType.BUTTON:
            note_mix_lines.append(f"(button(\"[{id}]{note_std}\") : si.smoo) * {func_name}")

        elif controller == ControllerType.HSLIDER:
            note_mix_lines.append(f"(hslider(\"[{id}]{note_std}\", 0, 0, 1, 0.1)) * {func_name}")

        single_file_lines = []
        single_file_lines.append(harmonic_functions)
        single_file_lines.append("")
        single_file_lines.append(f"process = {func_name};")

        with open(os.path.join(notes_faust_dir, f"{id}_{note_std}.dsp"), "w") as k:
            k.write("\n".join(init_lines))
            k.write("\n".join(single_file_lines))

        notes_lines.append(harmonic_functions)

    output_lines_button_selector = []
    output_lines_button_selector.append("\n")
    output_lines_button_selector.append("selector = " + " +\n           ".join(note_mix_lines) + ";")
    output_lines_button_selector.append("")
    output_lines_button_selector.append("process = selector * gain;")


    funcs_str = ", ".join(note_funcs)
    selector_line = f"selector = hslider(\"note\", 0, 0, {len(note_funcs)-1}, 1);"
    selectn_line = f"process = ba.selectn({len(note_funcs)}, selector, {funcs_str}) * gain;"
    
    output_lines_hslider_selector = []
    output_lines_hslider_selector.append("\n")
    output_lines_hslider_selector.append(selector_line)
    output_lines_hslider_selector.append("")
    output_lines_hslider_selector.append(selectn_line)

    with open(os.path.join(scripts_dir, "sax_synth_buttons.dsp"), "w") as f:
        f.write("\n".join(init_lines))
        f.write("\n".join(GAIN_LINES))
        f.write("\n".join(notes_lines))
        f.write("\n".join(output_lines_button_selector))

    with open(os.path.join(scripts_dir, "sax_synth_hslider.dsp"), "w") as f:
        f.write("\n".join(init_lines))
        f.write("\n".join(GAIN_LINES))
        f.write("\n".join(notes_lines))
        f.write("\n".join(output_lines_hslider_selector))
    
    with open(os.path.join(test_dir, "noise.dsp"), "w") as f:
        f.write("\n".join(TEST_FILE))

    print("Archivo FAUST 'sax_synth.dsp' generado con éxito.")

    destination_copy = {notes_faust_dir: os.path.join(base_dir, "../faust/single_notes/sax_single_notes_faust/"),
                       scripts_dir: os.path.join(base_dir, "../faust/sax_full/sax_full_faust/"),
                       test_dir: os.path.join(base_dir, "../faust/test_noise/")}
    
    for copy, paste in destination_copy.items():
        os.makedirs(paste, exist_ok=True)
        for fname in os.listdir(copy):
            shutil.copy(os.path.join(copy, fname), paste)

def valid_controller_type(s):
    try:
        return ControllerType(s)
    except ValueError:
        raise argparse.ArgumentTypeError(f"'{s}' no es un tipo válido. Opciones: {[e.value for e in ControllerType]}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-n",
        type=int, 
        nargs="?", 
        default=6, 
        help="Number of harmonics")
    parser.add_argument(
        "-t", "--type", 
        type=valid_controller_type,
        default=ControllerType.BUTTON,
        help="Type of controller")

    args = parser.parse_args()

    generate_files(args)
