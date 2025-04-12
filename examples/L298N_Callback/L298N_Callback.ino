#include <AlashMotorControl.h>

// Определите пины для вашего мотора
#define MOTOR_IN1 7 // Пример пина IN1
#define MOTOR_IN2 8 // Пример пина IN2
#define MOTOR_EN  9 // Пример пина Enable (PWM)

// Создаем экземпляр для L298N с пином Enable
AlashMotorControl motor(MOTOR_IN1, MOTOR_IN2, MOTOR_EN);

// Для TA6586:
// AlashMotorControl motor(MOTOR_IN1, MOTOR_IN2, DRIVER_TA6586);

bool moveComplete = false; // Флаг для отслеживания завершения движения

// Функция обратного вызова, которая будет вызвана после завершения движения
void motorStoppedCallback() {
  Serial.println("Движение завершено! Вызвана функция обратного вызова.");
  moveComplete = true; // Устанавливаем флаг
}

void setup() {
  Serial.begin(9600);
  Serial.println("AlashMotorControl - Пример Callback");

  motor.setSpeed(150); // Установим среднюю скорость
  Serial.println("Скорость установлена на 150.");

  Serial.println("Запускаем мотор вперед на 3 секунды с callback...");
  // Запускаем мотор вперед на 3000 мс (3 секунды)
  // После остановки будет вызвана функция motorStoppedCallback
  motor.forwardFor(3000, motorStoppedCallback);
}

void loop() {
  // Важно! В loop() нужно постоянно вызывать метод runFor/forwardFor/backwardFor,
  // чтобы библиотека могла проверить, не истекло ли время.
  // Вызываем его снова, но так как _lastMs уже не 0,
  // он будет только проверять время, а не запускать мотор заново.
  motor.forwardFor(3000, motorStoppedCallback);

  // Пример: можем делать что-то еще, пока мотор работает
  if (motor.isMoving()) {
     // Serial.print("."); // Печатаем точки, пока мотор движется
     delay(100); // Небольшая задержка, чтобы не перегружать Serial
  }

  // Когда callback установит флаг, мы можем выполнить какое-то действие
  if (moveComplete) {
    Serial.println("Флаг moveComplete установлен. Выполняем следующее действие.");
    delay(2000); // Ждем 2 секунды

    // Сбрасываем флаг и состояние таймера в моторе для следующего движения
    moveComplete = false;
    motor.reset(); // Позволяет снова использовать timed-функции

    Serial.println("Запускаем мотор назад на 2 секунды с callback...");
    // Запускаем мотор назад на 2000 мс (2 секунды) с тем же callback
    motor.backwardFor(2000, motorStoppedCallback);
  }

  // Вызываем backwardFor для проверки времени
  motor.backwardFor(2000, motorStoppedCallback);

}