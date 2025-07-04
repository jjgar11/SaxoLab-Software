#!/bin/bash

LOCAL_DIR=./dump_code
# Configuración remota
REMOTE_USER=root
REMOTE_HOST=192.168.1.17
REMOTE_DIR=/root/code/camargo

# Enviar todos los archivos del directorio actual
for file in ${LOCAL_DIR}/*; do
    echo "$file..."
    if [ -f "$file" ]; then
        echo "📤 Enviando $file..."
        scp -v "$file" "${REMOTE_USER}@${REMOTE_HOST}:${REMOTE_DIR}/"
    fi
done

echo "✅ Todos los archivos fueron enviados exitosamente."
