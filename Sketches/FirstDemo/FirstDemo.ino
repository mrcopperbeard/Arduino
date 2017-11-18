#include <math.h>

#define BUZZER_PIN 3
#define LED_PIN_1 9
#define LED_PIN_2 13
#define BUTTON_PIN 6
#define TERMO_PIN A0

bool enabled = false;
bool buttonWasUp = true;

void setup() {
  Serial.begin(9600);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  buttonWasUp =  handleClick(BUTTON_PIN);
    
  if (!enabled) {
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    
    return;
  }

  if (isTemperatureLowerThan(24.0)) {
    alarm();
  }

  digitalWrite(LED_PIN_2, HIGH);
}

bool isTemperatureLowerThan(float min) {
    float voltage = analogRead(TERMO_PIN) * 5.0 / 1023.0;
    float temperature = 1.0 / (log(voltage / 2.5) / 4300.0 + 1.0 / 298.0) - 273.0;

    delay(5000);

    Serial.println(temperature);
    
    return temperature < min;
}

bool handleClick(int buttonPin) {
    bool buttonPressed = !digitalRead(BUTTON_PIN);

    if (buttonWasUp && buttonPressed) {
      delay(10);
      buttonPressed = !digitalRead(BUTTON_PIN);
  
      if (buttonPressed) {
        enabled = !enabled;
      } 
    }

    return !buttonPressed;
}

void alarm() {
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, LOW);
    tone(BUZZER_PIN, 3700, 20);
    delay(250);

    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, HIGH);
    tone(BUZZER_PIN, 4200, 20);
    delay(250);
}
