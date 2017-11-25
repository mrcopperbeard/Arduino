#include <Servo.h>

#define SERVO_PIN 9
#define LED_PIN 13
#define POT_PIN A0

/// <summary>
/// Состояние (вкл/выкл).
/// </summary>
volatile bool enabled;

/// <summary>
/// Сервомотор.
/// </summary>
Servo servo;

/// <summary>
/// Инициализация компонентов.
/// </summary>
void setup() {
    enabled = false;
    servo.attach(SERVO_PIN);
    pinMode(LED_PIN, OUTPUT);

    // Подписываемся на обработчик нажатия кнопки.
    attachInterrupt(0, onButtonClick, RISING);
}

/// <summary>
/// Бесконечно-цикличная функция, исполняющая основную логику.
/// </summary>
void loop() {
  int ledSignal = 0;
  if (enabled) {
    int amplitude = getAmplitude(POT_PIN);
    move(amplitude);
    ledSignal = 100;
  }

  digitalWrite(LED_PIN, ledSignal);
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
  return map(inputSignal, 0, 1023, 0, 180);
}

/// <summary>
/// Движение сервомотора с заданной потенциометром амплитудой.
/// </summary>
/// <param name="amplitude">Амплитуда сервомотора.</param>
void move(int amplitude) {
  servo.write(amplitude);
  delay(500);
  servo.write(0);
    delay(500);
}

/// <summary>
/// Обработчик нажатия кнопки вкл/выкл.
/// </summary>
void onButtonClick() {
      enabled = !enabled;
}
