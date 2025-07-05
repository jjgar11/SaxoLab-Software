#!/bin/bash

# Configuración
LOCAL_DIR="saxophone_control"
REMOTE_HOST="emb_board_new"
REMOTE_DIR="/root/keyboard/saxophone_control"

# Crear estructura remota (por si no existe)
ssh "${REMOTE_HOST}" "mkdir -p ${REMOTE_DIR}"

# Enviar todos los archivos y subdirectorios uno por uno
for file in $(find "$LOCAL_DIR" -type f); do
    # Extraer ruta relativa
    rel_path="${file#$LOCAL_DIR/}"
    echo "${rel_path}"
    # Crear carpeta remota si no existe
    remote_path_dir=$(dirname "${REMOTE_DIR}/${rel_path}")
    ssh "${REMOTE_HOST}" "mkdir -p \"$remote_path_dir\""

    # Copiar archivo
    echo "${REMOTE_DIR}/${rel_path}"
    scp "$file" "${REMOTE_HOST}:${REMOTE_DIR}/${rel_path}"
done
