import("stdfaust.lib");

// Parámetros
freq = hslider("freq [midi]", 60, 40, 80, 1) : ba.midikey2hz;
gain = hslider("gain", 0.5, 0, 1, 0.01);

// Envolvente ADSR controlada por gate (tecla)
gate = button("gate");
env = en.adsr(0.01, 0.1, 0.7, 0.3, gate);

// Oscilador básico
sig = os.oscs(freq) * env * gain;

// Simulación de formantes (resonadores tipo saxofón)
formant1 = fi.resonbp(500, 100);   // Filtro pasabanda 1
formant2 = fi.resonbp(1000, 150);  // Filtro pasabanda 2
formant3 = fi.resonbp(2000, 300);  // Filtro pasabanda 3

process = sig : formant1 : formant2 : formant3 <: _, _;

