/*
   Автор    : Alash engineer
   Сайт     : https://alash-electronics.kz
   Исходник : https://github.com/Alash-electronics/AlashMotorControl

   Код демонстрирует управление скоростью и направлением вращения двигателя.
   Сначала устанавливается начальная скорость, затем двигатель вращается вперед, останавливается, изменяет скорость и вращается назад.
   Вся информация о состоянии двигателя выводится в Serial Monitor.
*/

#include <AlashMotorControl.h>

// Определяем пины для подключения мотора
const unsigned int PIN_IN1 = 4;
const unsigned int PIN_IN2 = 5;
const unsigned int PIN_EN = 6;

// Создаем экземпляр класса AlashMotorControl
AlashMotorControl motor(PIN_IN1, PIN_IN2, PIN_EN);

void setup() {
  Serial.begin(9600);    // Инициализация последовательного порта для отображения информации
  while (!Serial)  {     // Ожидание открытия Serial Monitor
    // ничего не делаем
  }
  motor.setSpeed(200);  // Устанавливаем начальную скорость мотора
}
void loop() {
  motor.forward();      // Команда для движения мотора вперед
  printMotorInfo();     // Выводим статус мотора в Serial Monitor
  delay(3000);
  motor.stop();         // Остановка мотора
  printMotorInfo();
  motor.setSpeed(255);   // Изменяем скорость мотора
  delay(3000);
  motor.backward();      // Команда для движения мотора назад
  printMotorInfo();
  motor.setSpeed(170);
  delay(3000);
  motor.stop();          // Остановка мотора
  printMotorInfo();
  delay(3000);
}
//Функция для вывода информации о моторе в Serial Monitor
void printMotorInfo() {
  Serial.print("Motor is moving = ");   // Выводим, движется ли мотор
  Serial.print(motor.isMoving());
  Serial.print(" at speed = ");         // Выводим текущую скорость мотора
  Serial.println(motor.getSpeed());
}
