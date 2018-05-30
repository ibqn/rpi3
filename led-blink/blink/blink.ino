const int led = 13;
bool state = true;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, (int)state);
  delay(1000);
  state = !state;
}
