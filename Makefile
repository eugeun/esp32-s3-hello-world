# ESP32-S3 (Freenove WROOM) — PlatformIO CLI wrapper
ENV  ?= freenove_s3
PIO  ?= pio
PORT ?=            # optional override: make upload PORT=/dev/tty.xxx

PORT_ARG := $(if $(PORT),--upload-port $(PORT),)
MON_ARG  := $(if $(PORT),--port $(PORT),)

.DEFAULT_GOAL := help
.PHONY: help setup build upload flash monitor run clean fullclean erase size devices compiledb check test

help: ## Show this help
	@grep -E '^[a-zA-Z_-]+:.*?## ' $(MAKEFILE_LIST) | awk 'BEGIN{FS=":.*?## "}{printf "  \033[36m%-10s\033[0m %s\n",$$1,$$2}'

setup: ## Install PlatformIO CLI (via pipx/pip) if missing
	@command -v $(PIO) >/dev/null || (command -v pipx >/dev/null && pipx install platformio || pip3 install --user platformio)

build: ## Compile firmware
	$(PIO) run -e $(ENV)

upload: ## Build and flash to board
	$(PIO) run -e $(ENV) -t upload $(PORT_ARG)

flash: upload ## Alias for upload

monitor: ## Serial monitor (with exception/backtrace decoder)
	$(PIO) device monitor -e $(ENV) $(MON_ARG)

run: ## Build, flash, then open monitor
	$(PIO) run -e $(ENV) -t upload $(PORT_ARG)
	$(PIO) device monitor -e $(ENV) $(MON_ARG)

clean: ## Remove build artifacts for this env
	$(PIO) run -e $(ENV) -t clean

fullclean: ## Remove entire .pio directory
	rm -rf .pio

erase: ## Erase entire flash
	$(PIO) run -e $(ENV) -t erase $(PORT_ARG)

size: ## Show firmware size
	$(PIO) run -e $(ENV) -t size

devices: ## List serial devices
	$(PIO) device list

compiledb: ## Generate compile_commands.json for IDE IntelliSense
	$(PIO) run -e $(ENV) -t compiledb

check: ## Static analysis (cppcheck)
	$(PIO) check -e $(ENV)

test: ## Run unit tests in test/
	$(PIO) test -e $(ENV)
