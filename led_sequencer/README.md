# LED Patterns

This program controls a row of 6 LEDs connected to pins 2–7.  
A pushbutton (on pin 8) is used to cycle through a sequence of 6 lighting patterns.

## Features

- Organize and run multiple LED animation patterns  
- Use software debounce for clean button input  
- Use function pointers to simplify pattern control  

## Hardware Setup

- LEDs connected to pins 2–7 (with 220Ω resistors)  
- Pushbutton connected to pin 8, configured with `INPUT_PULLUP`  
  - Button pressed = `LOW`  
  - Button released = `HIGH`  

## Demo

[![LED Patterns Demo](https://img.youtube.com/vi/aSmgeGWfAGg/hqdefault.jpg)](https://www.youtube.com/shorts/aSmgeGWfAGg)

