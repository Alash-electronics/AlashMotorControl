#ifndef ALASHMOTORDRIVERTYPE_H
#define ALASHMOTORDRIVERTYPE_H

// Enum to define the supported motor driver types
enum MotorDriverType {
    DRIVER_L298N,   // Standard L298N driver (IN1, IN2, optional EN)
    DRIVER_TA6586   // TA6586 / ZK-5AD driver (IN1, IN2, no EN, PWM on IN pins)
};

#endif // ALASHMOTORDRIVERTYPE_H