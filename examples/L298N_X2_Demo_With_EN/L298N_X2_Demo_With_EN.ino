/*
 * L298N_X2_Demo_With_EN.ino
 *
 * Демонстрация управления двумя моторами с драйвером L298N
 * с использованием пинов Enable для контроля скорости каждого мотора.
 *
 * Подключения:
 * Мотор A: D5->IN1A, D4->IN2A, D3(PWM)->ENA
 * Мотор B: D7->IN1B, D8->IN2B, D9(PWM)->ENB
 * Выходы драйвера -> Моторы
 * Питание L298N VCC/Vs и GND согласно документации.
 * УБЕДИТЕСЬ, ЧТО ПЕРЕМЫЧКИ ENA И ENB НА L298N СНЯТЫ!
 */

#include <AlashMotorControlX2.h> // Включаем библиотеку для двух моторов

// Пины для Мотора A
const int MOTOR_A_IN1_PIN = 5;
const int MOTOR_A_IN2_PIN = 4;
const int MOTOR_A_ENABLE_PIN = 3; // PWM

// Пины для Мотора B
const int MOTOR_B_IN1_PIN = 7;
const int MOTOR_B_IN2_PIN = 8;
const int MOTOR_B_ENABLE_PIN = 9; // PWM

// Создаем экземпляр AlashMotorControlX2 для двух L298N с пинами Enable
// Используем 6-пиновый конструктор и явно указываем тип драйвера для обоих
AlashMotorControlX2 motors(
    MOTOR_A_IN1_PIN, MOTOR_A_IN2_PIN, MOTOR_A_ENABLE_PIN, // Мотор A
    MOTOR_B_IN1_PIN, MOTOR_B_IN2_PIN, MOTOR_B_ENABLE_PIN, // Мотор B
    DRIVER_L298N,                                         // Тип драйвера A
    DRIVER_L298N                                          // Тип драйвера B
);

void setup() {
  Serial.begin(9600);
  Serial.println("L298N_X2 Demo with Enable Pins");

  // --- Индивидуальное управление ---
  Serial.println("\n--- Индивидуальное управление ---");
  Serial.println("Мотор A: Вперед, Скорость 200");
  motors.setSpeedA(200);
  motors.forwardA();
  delay(1500);

  Serial.println("Мотор B: Назад, Скорость 200");
  motors.setSpeedB(200);
  motors.backwardB();
  delay(1500);

  Serial.println("Мотор A: Стоп, Мотор B: Вперед, Скорость 200");
  motors.stopA();
  motors.setSpeedB(200);
  motors.forwardB();
  delay(1500);

  Serial.println("Мотор A: Назад (Тормоз), Мотор B: Стоп");
  motors.setSpeedA(200); // Скорость для торможения не важна, но лучше установить
  motors.HardStopA();    // Тормоз для A
  motors.stopB();        // Выбег для B
  delay(1000);

  // --- Синхронное управление ---
  Serial.println("\n--- Синхронное управление ---");
  Serial.println("Оба: Вперед, Скорость 150");
  motors.setSpeed(150);
  motors.forward();
  delay(2000);

  Serial.println("Оба: Назад, Скорость 150");
  motors.setSpeed(150);
  motors.backward();
  delay(2000);

  Serial.println("Оба: Стоп (Тормоз)");
  motors.HardStop();
  delay(1000);

   Serial.println("Оба: Стоп (Выбег)");
  motors.stop();
  delay(1000);

  Serial.println("\nДемо завершено.");
}

void loop() {
  // Ничего не делаем
}