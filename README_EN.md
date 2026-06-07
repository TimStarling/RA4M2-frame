<div align="right">

[中文](README.md) | [English](README_EN.md)

</div>

# RA4M2 Frame

`RA4M2-frame` is an embedded project template based on the Renesas RA4M2 MCU. It is suitable for course design, functional validation, and Renesas evaluation scenarios.

## Project Positioning

This is a minimal application framework that can be compiled and downloaded directly. It helps you quickly build feature-validation and assessment projects on top of an existing template.

- Complete FSP and user-layer structure
- Common peripheral modules such as keys, LEDs, UART, ADC, and timers
- Unified scheduling entry for extending business logic
- A test template for validating board-level functions step by step

## Structure

```text
.
├── src/                # User application code
├── ra_gen/             # FSP generated code
├── ra_cfg/             # FSP configuration headers
├── ra/fsp/             # FSP library source
├── renesas_prj.uvprojx # Keil project
└── README.md
```
