# Saxophone Project

Este proyecto permite interpretar teclas como notas de saxofón digital y enviarlas vía OSC a un sintetizador. Se divide en 3 modos:

- `sax_simple`: Solo imprime la nota por consola.
- `sax_osc`: Envía índice de nota y volumen por OSC.
- `sax_full`: Envía índice de nota y volumen proporcional a un sensor analógico (i2c).

## Requisitos
- librería `liblo`
- acceso a `/dev/input/eventX`
- si se usa `sax_full`, acceso a bus I2C `/dev/i2c-1`

## Compilación
```bash
make
```

## Ejecución
```bash
./sax_simple
./sax_osc
./sax_full
```
