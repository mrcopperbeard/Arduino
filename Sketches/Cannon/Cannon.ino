#include <Servo.h>

#define SERVO_PIN 9
#define LED_PIN 13
#define POT_PIN A0

/// <summary>
/// Сервомотор.
/// </summary>
Servo servo;

/// <summary>
/// Инициализация компонентов.
/// </summary>
void setup() {
    servo.attach(SERVO_PIN);
    pinMode(LED_PIN, OUTPUT);
}

/// <summary>
/// Бесконечно-цикличная функция, исполняющая основную логику.
/// </summary>
void loop() {
    move();
}

/// <summary>
/// Получение амплитуды сервомотора с потенциометра.
/// </summary>
/// <param name="inputPin">Вход потенциометра.</param>
/// <returns>Амплитуда потенциометра.</returns>
int getAmplitude(int inputPin) {
  // Читаем сигнал потенциометра в диапазоне 0-1023.
  int inputSignal = analogRead(inputPin);

  // Возвращаем значение в диапазоне 0-180.
  return map(inputSignal, 0, 1023, 0, 90);
}

/// <summary>
/// Движение сервомотора с заданной потенциометром амплитудой.
/// </summary>
/// <param name="amplitude">Амплитуда сервомотора.</param>
void move() {
  int amplitude = getAmplitude(POT_PIN);  
  servo.write(amplitude);
}
