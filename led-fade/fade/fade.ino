const int led = 9;     // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  analogWrite(led, brightness);

  // change the brightness for next time through the loop
  brightness += fadeAmount;

  // reverse the direction of the fading at the ends of the fade
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
