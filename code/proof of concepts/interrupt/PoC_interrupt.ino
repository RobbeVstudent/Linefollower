const int button = 2;
const int led = 6;
bool state = false;

void setup() {
  pinMode(button,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(button), blink, CHANGE);
}

void loop() {
  digitalWrite(led, state);
}

void blink() {
  state = !state;
}
