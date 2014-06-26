#define DEBUG 1

#include "Timer.h"
#include "Button.h"

#define PIN_ONBOARD_LED     13
#define PIN_VALVE_CONTROL   12
#define PIN_BUTTON_INPUT    2
#define PIN_SPEAKER_OUT     8

#ifdef DEBUG
#define VALVE_TIME  200
#else
// 1.5 min = 3x30s
#define VALVE_TIME  3 * 30 * 1000
#endif

Timer scheduler;
Button button( PIN_BUTTON_INPUT );

int valve_timer = -1;

void open_valve() {
  tone( PIN_SPEAKER_OUT, 440, 200 );
  scheduler.stop( valve_timer );
  valve_timer = scheduler.pulseImmediate( PIN_VALVE_CONTROL, VALVE_TIME, HIGH);
}

void setup() {                
  // initialize the digital pin as an output.
  // Pin PIN_ONBOARD_LED has an LED connected on most Arduino boards:
  pinMode(PIN_ONBOARD_LED, OUTPUT);
  digitalWrite(PIN_BUTTON_INPUT, LOW);

  // Setup water walve digital pin to close the valve
  pinMode(PIN_VALVE_CONTROL, OUTPUT);
  digitalWrite(PIN_BUTTON_INPUT, LOW);

  // blinking onboard led indicate running firmware
  scheduler.oscillate( PIN_ONBOARD_LED, 50, LOW );

  // button press callback
  button.on_press( open_valve );
}

void loop() {
  button.init();
  scheduler.update();
}
