/* 
 * This program controls a row of 6 LEDs connected to pins 2–7.
 * A pushbutton (on pin 8) is used to cycle through a sequence
 * of 6 lighting patterns.
 *
 * This project demonstrates:
 * - How to organize and run multiple LED animation patterns
 * - How to use software debounce for clean button input
 * - How to use function pointers to simplify pattern control
 *
 * Hardware setup:
 * - LEDs connected to pins 2–7 (with 220Ω resistors)
 * - Pushbutton connected to pin 8, configured with INPUT_PULLUP
 *   (button pressed = LOW, released = HIGH)
 */

const int SWITCH_PIN = 8;

int dir = 1;
unsigned led_cur = 2;
unsigned pattern_cur = 0;

// LED patterns
void one_by_one();
void two_by_two();
void one_by_one_bounce();
void two_by_two_bounce();
void fill_and_unfill();
void blink();

// Function pointers to LED patterns
// Note: use C-style as C++ std::function has a high overhead
void (*LED_PATTERNS[])() = {
  one_by_one,
  two_by_two,
  one_by_one_bounce,
  two_by_two_bounce,
  fill_and_unfill,
  blink,
};
constexpr size_t NUM_PATTERNS = sizeof(LED_PATTERNS) / sizeof(LED_PATTERNS[0]);

void reset_lights(){
  for (int i = 2; i < 8; ++i){
    digitalWrite(i, LOW);
  }
}

void one_by_one(){
  /*
   * Light up a single LEDs one-by-one. Start at Pin 2 and then increment until
   * Pin 7. This code has been adapted from The Arduino Projects Book's 
   * "Project 08: Digital Hourglass"
   *
   * t0:  100000
   * t1:  010000
   * t2:  001000
   * t3:  000100
   * t4:  000010
   * t5:  000001
   * t6:  000000
   */

  reset_lights();

  // Turn on the current LED
  digitalWrite(led_cur, HIGH);

  // Increment the LED position
  ++led_cur;

  // Reset to the beginning once it reaches the end
  if(led_cur == 9){
    led_cur = 2;
  }
}

void two_by_two(){
  /*
   * Light up a LEDs two at a time. Start at Pin 2 and then increment until
   * Pin 7.
   *
   * t0:  100000
   * t1:  110000
   * t2:  011000
   * t3:  001100
   * t4:  000110
   * t5:  000011
   * t6:  000001
   * t7:  000000
   */

  reset_lights();

  // Turn on the current LED
  digitalWrite(led_cur, HIGH);
  digitalWrite(led_cur-1, HIGH);

  // Increment the LED position
  ++led_cur;

  // Reset to the beginning once it reaches the end
  if(led_cur == 10){ 
    led_cur = 1;
  }
}


void one_by_one_bounce(){
  /*
   * Light up a single LEDs one-by-one. Start at Pin 2 and then increment until
   * Pin 7. Once it reaches Pin 7, decrement back to Pin 7.
   *
   * t0:  100000
   * t1:  010000
   * t2:  001000
   * t3:  000100
   * t4:  000010
   * t5:  000001
   * t6:  000010
   * t7:  000100
   * t8:  001000
   * t9:  010000
   * t10: 100000
   */

  reset_lights();

  // Turn on the current LED
  digitalWrite(led_cur, HIGH);

  // Increment or decrement the LED position
  led_cur += dir;

  // Change the direction once it reaches the end
  if(led_cur == 2){
    dir = 1;
  }else if(led_cur == 7){ 
    dir = -1;
  }
}

void two_by_two_bounce(){
  /*
   * Light up a LEDs two at a time. Start at Pin 2 and then increment until
   * Pin 7. Once it reaches Pin 7, decrement back to Pin 7.
   *
   * t0:  000000
   * t1:  100000
   * t2:  110000
   * t3:  011000
   * t4:  001100
   * t5:  000110
   * t6:  000011
   * t7:  000001
   * t8:  000000
   * t9:  000011
   * t10: 000110
   * t11: 001100
   * t12: 011000
   * t13: 110000
   * t14: 100000
   * t15: 000000
   */

  reset_lights();

  // Turn on the current LED
  digitalWrite(led_cur, HIGH);
  digitalWrite(led_cur+dir, HIGH);

  // Increment or decrement the LED position
  led_cur += dir;

  // Change the direction once it reaches the end
  if(led_cur == 0){
    dir = 1;
  }else if(led_cur == 9){ 
    dir = -1;
  }
}

void fill_and_unfill(){
  /*
   * Light up the entire row of LEDs, one at a time until all the lights are
   * on. Then turn them off, one by one until all the lights are off.
   *
   * t0:  000000
   * t1:  100000
   * t2:  110000
   * t3:  111000
   * t4:  111100
   * t5:  111110
   * t6:  111111
   * t7:  111110
   * t8:  111100
   * t9:  111000
   * t10: 110000
   * t11: 100000
   * t12: 000000
   */
  
  reset_lights();

  // Turn on the current LED and the ones prior to it
  for (int i = 2; i <= led_cur; ++i){
    digitalWrite(i, HIGH);
  }
  
  // Increment or decrement the LED position
  led_cur += dir;

  // Change the direction once it reaches the end
  if(led_cur == 1){
    dir = 1;
  }else if(led_cur == 7){ 
    dir = -1;
  }
}

void blink(){
  /*
   * Light up every other pin. Switch back and forth between pins.
   *
   * t0:  101010
   * t1:  010101
   */

  reset_lights();

  // Turn on the current LED
  digitalWrite(led_cur, HIGH);
  digitalWrite(led_cur+2, HIGH);
  digitalWrite(led_cur+4, HIGH);

  // Switch the lights
  if(led_cur == 2){ 
    led_cur = 3;
  }else if(led_cur == 3){
    led_cur = 2;
  }
}

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  for(int i = 2; i < 8; ++i){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // Constants
  const unsigned long LED_PATTERN_SPEED = 150;
  const unsigned long DEBOUNCE = 50;

  // Timestamp variables
  unsigned long ts_cur = millis();
  static unsigned long ts_prev = 0;
  static unsigned long ts_prev_debounce = 0; // last stable reading
  
  // Switch state variables
  // LOW (0) when pressed, otherwise HIGH (1) due to INPUT_PULLUP
  int state = digitalRead(SWITCH_PIN);
  static int prev_state = HIGH;
  static int prev_debounce_state = HIGH; // last stable reading

  // Record whether the signal has switched from the previous state
  if(state != prev_state){
    ts_prev_debounce = ts_cur;
    prev_state = state;
  }

  // The signal in between state switches needs to be sustained for at least 
  // 50ms. Otherwise, the "bouncy" signal from the first few ms of pressing the
  // button will not read cleanly. If the LOW signal is settled (ie. the button
  // is being pressed), increment to the next pattern
  if((ts_cur - ts_prev_debounce) > DEBOUNCE && state != prev_debounce_state){
    prev_debounce_state = state;

    if(prev_debounce_state == LOW){
      reset_lights();
      led_cur = 2;
      dir = 1;
      pattern_cur = (pattern_cur + 1) % NUM_PATTERNS;
    }
  }

  // The pattern runs at 150ms/cycle
  if((ts_cur - ts_prev) > LED_PATTERN_SPEED){
    ts_prev = ts_cur;
    LED_PATTERNS[pattern_cur]();
  }
}

