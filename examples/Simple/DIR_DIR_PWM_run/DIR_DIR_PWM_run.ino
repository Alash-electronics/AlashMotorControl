/*
  Автор    : Alash engineer
  Сайт     : https://alash-electronics.kz
  Исходник : https://github.com/Alash-electronics/AlashMotorControl

  Пример работы с AlashMotorControl для управления двигателем постоянного тока.
  Код демонстрирует управление скоростью и направлением вращения двигателя.
  Для управления используется метод run().
  Написан для Alash engineering.
*/

#include <AlashMotorControl.h>

// Определяем пины для подключения мотора
const unsigned int PIN_FORWARD = 4;
const unsigned int PIN_BACKWARD = 5;
const unsigned int PIN_ENABLE = 6;

// Создаем экземпляр класса AlashMotorControl
AlashMotorControl motor(PIN_FORWARD, PIN_BACKWARD, PIN_ENABLE);

void setup() {
  Serial.begin(9600);    // Инициализация последовательного порта для отображения информации
  while (!Serial) {      // Ожидание открытия Serial Monitor
    // ничего не делаем
  }
  motor.setSpeed(200);   // Устанавливаем начальную скорость мотора
}

void loop() {
  motor.run(AlashMotorControl::FORWARD);  // Команда для движения мотора вперед
  printMotorStatus();     // Выводим статус мотора в Serial Monitor
  delay(3000);
  
  motor.run(AlashMotorControl::STOP);     // Остановка мотора
  printMotorStatus();
  motor.setSpeed(255);    // Изменяем скорость мотора
  delay(3000);
  
  motor.run(AlashMotorControl::BACKWARD); // Команда для движения мотора назад
  printMotorStatus();
  motor.setSpeed(170);
  delay(3000);
  
  motor.run(AlashMotorControl::STOP);     // Остановка мотора
  printMotorStatus();
  delay(3000);
}

// Функция для вывода информации о моторе в Serial Monitor
void printMotorStatus() {
  Serial.print("Motor is moving = ");   // Выводим, движется ли мотор
  Serial.print(motor.isMoving());
  Serial.print(" at speed = ");         // Выводим текущую скорость мотора
  Serial.println(motor.getSpeed());
}
