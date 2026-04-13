#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
FIRMWARE_DIR="$ROOT_DIR/firmware"

PIO_BIN="$ROOT_DIR/.venv/bin/pio"
if [[ ! -x "$PIO_BIN" ]]; then
  if command -v pio >/dev/null 2>&1; then
    PIO_BIN="$(command -v pio)"
  else
    echo "Error: PlatformIO not found."
    echo "Install via workspace venv or system package, then retry."
    exit 1
  fi
fi

echo "Using PlatformIO: $PIO_BIN"
cd "$FIRMWARE_DIR"
exec "$PIO_BIN" run -e heltec_wifi_lora_32_V2_sim
