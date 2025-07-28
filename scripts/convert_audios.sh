#!/bin/bash

# Carpeta de entrada (con tus .m4a, .mp3, etc.)
INPUT_DIR="saxophone_control/audios"

# Carpeta de salida
OUTPUT_DIR="saxophone_control/audios_wav"
mkdir -p "$OUTPUT_DIR"

# Extensiones de audio que quieres convertir
EXTENSIONS=("m4a" "mp3" "ogg" "wav")

# Recorrer archivos con extensiones soportadas
for ext in "${EXTENSIONS[@]}"; do
    for file in "$INPUT_DIR"/*."$ext"; do
        [ -e "$file" ] || continue  # Si no hay archivos, salta
        filename=$(basename -- "$file")
        name="${filename%.*}"
        output="$OUTPUT_DIR/$name.wav"

        echo "Convirtiendo $file → $output"
        ffmpeg -y -i "$file" -ar 16000 -ac 1 -sample_fmt s16 "$output"
    done
done

echo "✅ Conversión terminada. Archivos en: $OUTPUT_DIR/"
