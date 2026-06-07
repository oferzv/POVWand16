# POVWand16

POVWand16 is a 16 LED persistence-of-vision wand. When the wand is moved
through the air, the firmware flashes a vertical column of LEDs fast enough
that the viewer sees complete text or simple bitmap graphics suspended in the
motion path.

The repository contains both sides of the project:

- Arduino firmware for driving the LED column and selecting messages or
  graphics.
- Autodesk Eagle schematic and board layout files for the custom PCB.
- Manufacturing outputs, including a BOM spreadsheet and Gerber archive.

## Project Overview

The design is based around an Arduino Nano-compatible controller connected to
16 individual LEDs. Each LED has its own 100 ohm series resistor. The firmware
writes directly to the AVR port registers for speed, allowing all 16 LEDs to be
updated as a two-byte column pattern.

A trigger input on Arduino analog pin A4 is used to step through the available
display content. The current firmware alternates between text messages and
graphics. Text can be rendered with either the English font table or the Hebrew
font table stored in program memory.

The hardware is intended to be a self-contained handheld wand. The PCB includes
the Arduino Nano footprint, the LED column, a 9 V battery holder, a power slide
switch, a tactile switch, and several header connectors.

## Repository Layout

```text
.
+-- Firmware
|   +-- README.md
|   +-- POVWand16_SW_heb
|       +-- POVWand16.ino
|       +-- font.h
|       +-- python
|           +-- pandaTestFormat.py
+-- Hardware
|   +-- V1_1
|       +-- Eagle
|       |   +-- POVWand16.brd
|       |   +-- POVWand16.sch
|       +-- Manufacturing
|           +-- BOM
|           |   +-- POVWand16_BOM.xlsx
|           +-- Gerber
|               +-- POVWand16_2020-03-09.zip
+-- README.md
```

## Hardware

The hardware design files live under `Hardware/V1_1`.

Main board elements:

- Arduino Nano 3.0-compatible module footprint.
- 16 through-hole 3 mm LEDs labeled `D1` through `D16`.
- 16 through-hole 100 ohm LED current-limiting resistors labeled `R1` through
  `R16`.
- 9 V battery holder footprint.
- Slide power switch.
- 6 mm momentary tactile switch.
- Additional 1x08 and 1x18 headers for board connections and expansion.

The Eagle files are:

- `Hardware/V1_1/Eagle/POVWand16.sch` - schematic.
- `Hardware/V1_1/Eagle/POVWand16.brd` - PCB layout.

Manufacturing files are:

- `Hardware/V1_1/Manufacturing/BOM/POVWand16_BOM.xlsx` - bill of materials.
- `Hardware/V1_1/Manufacturing/Gerber/POVWand16_2020-03-09.zip` - Gerber
  output for PCB fabrication.

## Firmware

The firmware is an Arduino sketch located at:

```text
Firmware/POVWand16_SW_heb/POVWand16.ino
```

Supporting files:

- `font.h` contains the English and Hebrew font tables in `PROGMEM`.
- `python/pandaTestFormat.py` is a small helper script for converting Hebrew
  text into the character order/encoding expected by the sketch.

The sketch uses Arduino pins 2 through 17 as the 16 LED outputs:

```cpp
const byte LEDpins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
```

The trigger input is on pin 18, which corresponds to Arduino A4:

```cpp
const byte triggerPin = 18;
```

Display timing is controlled by three constants:

- `charDelay` - spacing between characters.
- `tColDelay` - spacing between text columns.
- `gColDelay` - spacing between graphic columns.

The current firmware defines six text messages and two graphics. A trigger
press advances through the text messages, then advances through the graphics,
then returns to the first text message.

## Display Content

Text messages are defined in `POVWand16.ino` as `PROGMEM` strings:

```cpp
const char textString01 [] PROGMEM = "ARDIUNO - fqjafdya";
const char textString02 [] PROGMEM = "eqfyfxe jyha eay{q";
const char textString03 [] PROGMEM = "BRAVO!";
const char textString04 [] PROGMEM = "Hello";
const char textString05 [] PROGMEM = "WOW!";
const char textString06 [] PROGMEM = "Amazing";
```

Each message is paired with a font type in the `messages_new` table:

- `HEBFONT` selects the Hebrew font table.
- `ENGFONT` selects the English font table.

Graphics are stored as byte arrays in the `graphic` table. Each displayed
column is represented by two bytes, covering the full 16 LED height.

## Building and Uploading

Open `Firmware/POVWand16_SW_heb/POVWand16.ino` in the Arduino IDE or another
Arduino-compatible build environment.

Recommended target:

- Board: Arduino Nano or compatible.
- Processor: the option matching the installed Nano bootloader.
- Upload method: standard USB serial upload through the Nano.

After upload, power the wand and move it through the air. Use the trigger input
to cycle through the stored text and graphic displays.

## Customization Notes

To change displayed text:

1. Edit the `textStringXX` constants in `POVWand16.ino`.
2. Set each message's font type in `messages_new`.
3. Update `NUMBER_OF_ELEMENTS` if the number of messages changes.

To change graphics:

1. Edit the byte arrays in the `graphic` table.
2. Keep each graphic encoded as pairs of bytes per column.
3. Adjust the timing constants if the image appears stretched or compressed
   while waving the wand.

To change LED wiring:

1. Update `LEDpins` if using the slower `digitalWrite` helper path.
2. Update `setPorts()` if changing the direct AVR port mapping used by the
   main display loop.

## Attribution

The firmware is based on the JolliPOV Stick Arduino code from the Instructables
project
[Arduino Based POV Display Stick - JolliPOV Stick](https://www.instructables.com/Arduino-Based-POV-Display-Stick-JolliPOV-Stick/)
by [jollifactory](https://www.instructables.com/member/jollifactory/).

Credit and thanks to the original author for publishing the JolliPOV Stick
project instructions and example firmware.
