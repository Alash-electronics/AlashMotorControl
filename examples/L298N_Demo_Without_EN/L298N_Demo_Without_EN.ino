/*
 * L298N_Demo_Without_EN.ino
 *
 * Демонстрация управления одним мотором с драйвером L298N
 * БЕЗ использования пина Enable (предполагается, что он подключен к 5V
 * через перемычку на плате L298N). Скорость не регулируется (всегда максимальная).
 *
 * Подключения:
 * Arduino D5 -> L298N IN1
 * Arduino D4 -> L298N IN2
 * Выходы L298N OUT1/OUT2 -> Мотор
 * Питание L298N VCC/Vs и GND согласно документации.
 * УБЕДИТЕСЬ, ЧТО ПЕРЕМЫЧКА ENA (ИЛИ ENB) НА L298N УСТАНОВЛЕНА!
 */

#include <AlashMotorControl.h> // Используем базовую библиотеку

// Пины управления мотором
const int MOTOR_IN1_PIN = 5;
const int MOTOR_IN2_PIN = 4;

// Создаем экземпляр AlashMotorControl для L298N без пина Enable
// Используем 2-пиновый конструктор и явно указываем тип драйвера
AlashMotorControl motor(MOTOR_IN1_PIN, MOTOR_IN2_PIN, DRIVER_L298N);

void setup() {
  Serial.begin(9600);
  Serial.println("L298N Demo without Enable Pin (Jumpered)");
  Serial.println("Скорость не регулируется, всегда максимальная.");

  // setSpeed() не будет иметь эффекта, так как пин Enable не используется
  // motor.setSpeed(100); // Этот вызов не изменит скорость

  Serial.println("Мотор Вперед (Макс Скорость)");
  motor.forward();
  delay(2000);

  Serial.println("Мотор Назад (Макс Скорость)");
  motor.backward();
  delay(2000);

  Serial.println("Остановка (Выбег)");
  motor.stop();
  delay(1000);

  Serial.println("Остановка (Тормоз)");
  motor.HardStop();
  delay(1000);

  Serial.println("Демо завершено.");
}

void loop() {
  // Ничего не делаем в цикле
}