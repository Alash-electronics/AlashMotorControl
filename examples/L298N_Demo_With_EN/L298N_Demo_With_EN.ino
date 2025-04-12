/*
 * L298N_Demo_With_EN.ino
 *
 * Демонстрация управления одним мотором с драйвером L298N
 * с использованием пина Enable для контроля скорости.
 *
 * Подключения:
 * Arduino D5 -> L298N IN1
 * Arduino D4 -> L298N IN2
 * Arduino D3 (PWM) -> L298N ENA (или ENB)
 * Выходы L298N OUT1/OUT2 -> Мотор
 * Питание L298N VCC/Vs и GND согласно документации.
 * УБЕДИТЕСЬ, ЧТО ПЕРЕМЫЧКА ENA (ИЛИ ENB) НА L298N СНЯТА!
 */

#include <AlashMotorControl.h> // Используем базовую библиотеку

// Пины управления мотором
const int MOTOR_IN1_PIN = 5;
const int MOTOR_IN2_PIN = 4;
const int MOTOR_ENABLE_PIN = 3; // Должен быть PWM пин

// Создаем экземпляр AlashMotorControl для L298N с пином Enable
// Используем 3-пиновый конструктор и явно указываем тип драйвера
AlashMotorControl motor(MOTOR_IN1_PIN, MOTOR_IN2_PIN, MOTOR_ENABLE_PIN, DRIVER_L298N);

void setup() {
  Serial.begin(9600);
  Serial.println("L298N Demo with Enable Pin");

  Serial.println("Мотор Вперед, Скорость 100");
  motor.setSpeed(100);
  motor.forward();
  delay(2000);

  Serial.println("Мотор Назад, Скорость 200");
  motor.setSpeed(200);
  motor.backward();
  delay(2000);

  Serial.println("Мотор Вперед, Макс Скорость");
  motor.setSpeed(255);
  motor.forward();
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