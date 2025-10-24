# 8-Button Analog Keyboard / Digital Synthesizer for Arduino 

This project implements a **full octave keyboard from C4 to C5** using 8 buttons wired in a **uniform series resistor ladder (7 x 10kΩ)**. The keyboard uses a **single analog input (A0)** on an Arduino and outputs sound to a **piezo speaker (pin 8)**.

This code is **adapted and extended from The Arduino Projects Book**, *Project 07: "Keyboard Instrument"*, which originally supported only 4 frequencies.

## Simple Song Index Mappings

**Daisy Bell**
```
4 2 1 0 0 1 2 3 5 4
3 5 2 0 0 1 2 3 5 4
4 5 4 6 5 2 1 4 5 4 3 4 3 2
5 6 6 5 3 4 2 0
```

**Mary Had a Little Lamb**
```
2 1 0 1 2 2 2 1 1 1 2 4 4
2 1 0 1 2 2 2 2 1 1 2 1 0
```

**Twinkle Twinkle Little Star**
```
0 0 4 4 5 5 4 3 3 2 2 1 1 0
4 4 3 3 2 2 1 4 4 3 3 2 2 1
0 0 4 4 5 5 4 3 3 2 2 1 1 0
```
