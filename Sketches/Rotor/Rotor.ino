#define MOTOR_PIN 9
#define BUTTON_PIN 7

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(BUTTON_PIN)) 
  {
    tone(MOTOR_PIN, 75, 20);
  }
 
}
