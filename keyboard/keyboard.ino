/* 
 * Full octave keyboard from C4 to C5. The 8 buttons are wired in a uniform 
 * series resistor ladder (7 x 10kΩ) for a single-pin input (A0) and output to
 * piezo (pin 8). 
 *
 * This code is adapted and extended from The Arduino Projects Book's 
 * "Project 07: Keyboard Instrument," which is originally supported only
 * 4 frequencies.
 *
 */
 
const int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

void setup() {
  Serial.begin(9600);
}

void loop() {
  int keyVal = analogRead(A0);
  Serial.println(keyVal);

  if(keyVal >= 1000){      // C: 262Hz
    tone(8, notes[0]);
  }else if(keyVal >= 495){ // D: 294Hz
    tone(8, notes[1]);
  }else if(keyVal >= 325){ // E: 330Hz
    tone(8, notes[2]);
  }else if(keyVal >= 240){ // F: 349Hz
    tone(8, notes[3]);
  }else if(keyVal >= 190){ // G: 392Hz
    tone(8, notes[4]);
  }else if(keyVal >= 155){ // A: 440Hz
    tone(8, notes[5]);
  }else if(keyVal >= 130){ // B: 494Hz
    tone(8, notes[6]);
  }else if(keyVal >= 100){ // C: 523Hz
    tone(8, notes[7]);
  }else{
    noTone(8);
  }
}