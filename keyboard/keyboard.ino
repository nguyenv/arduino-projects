// Full octave keyboard using a uniform resistor ladder (7 x 10kΩ).

// Daisy Bell
// 4 2 1 0 0 1 2 3 5 4
// 3 5 2 0 0 1 2 3 5 4
// 4 5 4 6 5 2 1 4 5 4 3 4 3 2
// 5 6 6 5 3 4 2 0

// Mary Had a Little Lamb
// 2 1 0 1 2 2 2 1 1 1 2 4 4
// 2 1 0 1 2 2 2 2 1 1 2 1 0

// Twinkle Twinkle Little Star
// 0 0 4 4 5 5 4 3 3 2 2 1 1 0
// 4 4 3 3 2 2 1 4 4 3 3 2 2 1
// 0 0 4 4 5 5 4 3 3 2 2 1 1 0

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