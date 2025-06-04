#!/bin/bash

EXEC_DIR="$HOME/faust/single_notes/compiled_notes"
CURRENT_PID=""

# Manejador para matar el proceso hijo si se interrumpe el script
cleanup() {
    if [[ -n "$CURRENT_PID" ]]; then
        echo "Terminando proceso $CURRENT_PID..."
        kill "$CURRENT_PID" 2>/dev/null
        wait "$CURRENT_PID" 2>/dev/null
    fi
    exit 1
}

trap cleanup SIGINT SIGTERM

for exe in "$EXEC_DIR"/*; do
    if [[ -x "$exe" && ! -d "$exe" ]]; then
        echo "Ejecutando $exe ..."
        
        "$exe" &
        CURRENT_PID=$!

        sleep 1

        kill "$CURRENT_PID" 2>/dev/null
        wait "$CURRENT_PID" 2>/dev/null

        CURRENT_PID=""
        echo "Finalizado $exe"
        echo "-----------------------------"
    fi
done

