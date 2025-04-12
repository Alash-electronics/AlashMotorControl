/*
 * L298N_X2_Demo_Without_EN.ino
 *
 * Демонстрация управления двумя моторами с драйвером L298N
 * БЕЗ использования пинов Enable (предполагается, что ENA и ENB
 * подключены к 5V через перемычки). Скорость не регулируется.
 *
 * Подключения:
 * Мотор A: D5->IN1A, D4->IN2A
 * Мотор B: D7->IN1B, D8->IN2B
 * Выходы драйвера -> Моторы
 * Питание L298N VCC/Vs и GND согласно документации.
 * УБЕДИТЕСЬ, ЧТО ПЕРЕМЫЧКИ ENA И ENB НА L298N УСТАНОВЛЕНЫ!
 */

#include <AlashMotorControlX2.h> // Включаем библиотеку для двух моторов

// Пины для Мотора A
const int MOTOR_A_IN1_PIN = 5;
const int MOTOR_A_IN2_PIN = 4;

// Пины для Мотора B
const int MOTOR_B_IN1_PIN = 7;
const int MOTOR_B_IN2_PIN = 8;

// Создаем экземпляр AlashMotorControlX2 для двух L298N без пинов Enable
// Используем 4-пиновый конструктор и явно указываем тип драйвера для обоих
AlashMotorControlX2 motors(
    MOTOR_A_IN1_PIN, MOTOR_A_IN2_PIN,   // Мотор A
    MOTOR_B_IN1_PIN, MOTOR_B_IN2_PIN,   // Мотор B
    DRIVER_L298N,                       // Тип драйвера A
    DRIVER_L298N                        // Тип драйвера B
);

void setup() {
  Serial.begin(9600);
  Serial.println("L298N_X2 Demo without Enable Pins (Jumpers ON)");
  Serial.println("Скорость не регулируется, всегда максимальная.");

  // setSpeed(), setSpeedA(), setSpeedB() не будут иметь эффекта

  // --- Индивидуальное управление ---
  Serial.println("\n--- Индивидуальное управление ---");
  Serial.println("Мотор A: Вперед");
  motors.forwardA();
  delay(1500);
  Serial.println("Мотор B: Назад");
  motors.backwardB();
  delay(1500);
  Serial.println("Мотор A: Стоп, Мотор B: Вперед");
  motors.stopA();
  motors.forwardB();
  delay(1500);
  Serial.println("Мотор A: Назад (Тормоз), Мотор B: Стоп (Выбег)");
  motors.HardStopA();
  motors.stopB();
  delay(1000);

  // --- Синхронное управление ---
  Serial.println("\n--- Синхронное управление ---");
  Serial.println("Оба: Вперед");
  motors.forward();
  delay(2000);
  Serial.println("Оба: Назад");
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