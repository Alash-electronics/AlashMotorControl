/*
 * Two_TA6586_Demo.ino
 *
 * Демонстрация управления двумя моторами с драйверами TA6586
 * с использованием библиотеки AlashMotorControlX2.
 *
 * Подключения:
 * Мотор A: Arduino D5 -> IN1_A, Arduino D6 -> IN2_A
 * Мотор B: Arduino D9 -> IN1_B, Arduino D10 -> IN2_B
 * Питание драйверов и GND согласно документации.
 */

#include <AlashMotorControlX2.h> // Включаем библиотеку для двух моторов

// Пины для Мотора A (TA6586)
const int MOTOR_A_IN1_PIN = 5;
const int MOTOR_A_IN2_PIN = 6;

// Пины для Мотора B (TA6586)
const int MOTOR_B_IN1_PIN = 9;
const int MOTOR_B_IN2_PIN = 10;

// Создаем экземпляр AlashMotorControlX2 для двух моторов TA6586
// Используем конструктор для 4-х пинов управления (без Enable)
// Указываем тип драйвера DRIVER_TA6586 для обоих моторов
AlashMotorControlX2 motors(
    MOTOR_A_IN1_PIN, MOTOR_A_IN2_PIN,   // Пины мотора A
    MOTOR_B_IN1_PIN, MOTOR_B_IN2_PIN,   // Пины мотора B
    DRIVER_TA6586,                      // Тип драйвера для мотора A
    DRIVER_TA6586                       // Тип драйвера для мотора B
);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Ожидание подключения к последовательному порту
  }
  Serial.println("AlashMotorControlX2 - Демо для двух TA6586");

  // --- Демонстрация индивидуального управления ---
  Serial.println("\n--- Индивидуальное управление ---");

  Serial.println("Мотор A: Вперед, Скорость 150");
  motors.setSpeedA(150);
  motors.forwardA();
  delay(2000);

  Serial.println("Мотор B: Назад, Скорость 200");
  motors.setSpeedB(200);
  motors.backwardB();
  delay(2000);

  Serial.println("Мотор A: Стоп");
  motors.stopA(); // Coast stop
  Serial.println("Мотор B: Стоп (Тормоз)");
  motors.HardStopB(); // Brake stop
  delay(1000);


  // --- Демонстрация синхронного управления ---
  Serial.println("\n--- Синхронное управление ---");

  Serial.println("Оба мотора: Вперед, Скорость 255");
  motors.setSpeed(255); // Установить скорость для обоих
  motors.forward();     // Запустить оба вперед
  delay(2000);

  Serial.println("Оба мотора: Назад, Скорость 100");
  motors.setSpeed(100);
  motors.backward();    // Запустить оба назад
  delay(2000);

  Serial.println("Оба мотора: Стоп (Тормоз)");
  motors.HardStop();    // Остановить оба (торможение)
  delay(1000);

    Serial.println("Оба мотора: Стоп (Выбег)");
  motors.stop();    // Остановить оба (выбег)
  delay(1000);

  Serial.println("\nДемонстрация завершена.");
}

void loop() {
  // В этом примере основная логика в setup()
  // Здесь можно добавить управление по командам из Serial порта и т.д.
}