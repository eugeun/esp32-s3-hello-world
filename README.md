# ESP32-S3 Blinking LED

Arduino-framework firmware for the Freenove ESP32-S3 WROOM board (8MB flash, QIO/OPI PSRAM), built with PlatformIO and driven by a Makefile.

## Setup on a new workstation

1. Install PlatformIO CLI: `make setup` (or install the PlatformIO IDE extension in VSCode; the Makefile finds `~/.platformio/penv/bin/pio` automatically).
2. Install the VSCode *C/C++* extension.
3. Connect the board and find its port: `make devices`.
4. Set `upload_port` and `monitor_port` in [platformio.ini](platformio.ini), or pass `PORT=/dev/tty.xxx` to make.
5. Generate IntelliSense data: `make compiledb` (the first run downloads the toolchain, ~2 min).
6. Reload the VSCode window.

## Develop

Code lives in `src/` (headers in `include/`, local libraries in `lib/`, unit tests in `test/`).

| Command | Action |
|---|---|
| `make build` | Compile |
| `make upload` | Build and flash |
| `make monitor` | Serial monitor (decodes crash backtraces) |
| `make run` | Build, flash, monitor |
| `make size` / `make clean` / `make fullclean` | Size report / clean / wipe `.pio` |
| `make erase` | Erase flash |
| `make check` / `make test` | Static analysis / unit tests |
| `make compiledb` | Refresh `compile_commands.json` |

`make help` lists all targets.

**Debugging** is serial-only: use `Serial.printf` and the `CORE_DEBUG_LEVEL=3` log output. There is no JTAG/GDB setup.

**LED pin:** set with `-DLED_PIN=2` in `platformio.ini`.

## Add libraries

1. Add to `platformio.ini` under `[env:freenove_s3]` (search at <https://registry.platformio.org>):
   ```ini
   lib_deps =
       adafruit/Adafruit NeoPixel @ ^1.12.0
   ```
2. `#include` it in your code and run `make build` (it downloads on first build).
3. Run `make compiledb` so VSCode finds the new headers and the red squiggle goes away.

Local libraries: put them in `lib/<name>/` (no `lib_deps` entry needed).

## Troubleshooting

- *"include errors detected" in VSCode:* run `make compiledb`, then reload the window.
- *Upload fails / port not found:* check `make devices`; the USB-serial path changes if you use another port or board.
