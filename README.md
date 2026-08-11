# Arduino TFT Photo Display

An Arduino-based TFT photo display that loads and cycles through bitmap images stored on an SD card. This project combines an Adafruit TFT display, SD card storage, and SPI communication to create a standalone image slideshow with a custom animated startup sequence.

## Overview

This project explores embedded hardware, display control, SD card storage, and communication between multiple peripherals over SPI.

When powered on, the system:

1. Initializes the TFT display and SD card.
2. Displays a custom **"Welcome!"** startup screen.
3. Runs an animated pattern of purple circles across the display.
4. Loads BMP images from an SD card.
5. Displays each image sequentially on the TFT display.
6. Continuously loops through the image collection.

Once programmed and loaded with images, the display operates as a standalone embedded system without requiring a computer.

## Hardware

- Arduino-compatible microcontroller
- Adafruit HX8357 TFT display
- SD card
- SD card interface
- SPI-connected peripherals
- Custom hardware wiring

### SPI Configuration

The TFT display and SD card share the same SPI communication lines while using separate Chip Select pins.

| Component | Pin |
|---|---:|
| SD Card CS | 5 |
| TFT CS | 9 |
| TFT DC | 10 |

Separate Chip Select pins allow the Arduino to communicate with the TFT display and SD card independently while sharing the SPI bus.

## Software & Libraries

- C++ / Arduino
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit HX8357 Library](https://github.com/adafruit/Adafruit_HX8357)
- [SdFat](https://github.com/greiman/SdFat)
- [Adafruit ImageReader](https://github.com/adafruit/Adafruit_ImageReader)

The project uses and adapts functionality from Adafruit's `Adafruit_ImageReader` library and example sketches for loading BMP images from an SD card and rendering them on a TFT display.

Project-specific code includes the welcome screen, startup animation, image list management, slideshow logic, and hardware configuration.

## Project Photos

<div align="center">

<table>
<tr>
<td align="center">
<img src="media/front.png" width="400">
<br>
<b>Front</b>
</td>
<td align="center">
<img src="media/whole.png" width="400">
<br>
<b>Full Assembly</b>
</td>
</tr>

<tr>
<td align="center">
<img src="media/inside.png" width="400">
<br>
<b>Internal Components</b>
</td>
<td align="center">
<img src="media/back.png" width="400">
<br>
<b>Back</b>
</td>
</tr>
</table>

</div>

## Demo

[▶️ Watch the Demo](media/demo.mov)

The demonstration shows the display powering on, running the custom startup animation, and cycling through the stored photographs.

## Image Slideshow

The images displayed by the project are stored on the SD card as BMP files and referenced by an array in the Arduino program:

```cpp
const char* imageFiles[] = {
    "mama.bmp",
    "main.bmp",
    "shriya.bmp",
    "close.bmp"
};

