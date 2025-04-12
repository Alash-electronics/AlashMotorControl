#ifndef AlashMotorControl_h
#define AlashMotorControl_h

#include "Arduino.h"
#include "AlashMotorDriverType.h" // Include the new enum definition

typedef void (*CallBackFunction)();

class AlashMotorControl{
public:
   typedef enum
   {
      FORWARD = 0,
      BACKWARD = 1,
      STOP = -1 // Coast stop
   } Direction;

   // --- Constructors ---
   // Constructor for drivers with separate Enable pin (like L298N)
   // Defaults to L298N for backward compatibility
   AlashMotorControl(uint8_t pinIN1, uint8_t pinIN2, uint8_t pinEnable, MotorDriverType driverType = DRIVER_L298N);

   // Constructor for drivers without separate Enable pin (like TA6586 or L298N with EN jumpered)
   // Defaults to L298N for backward compatibility (assumes jumpered EN)
   // For TA6586, pinIN1 and pinIN2 handle both direction and speed (PWM)
   AlashMotorControl(uint8_t pinIN1, uint8_t pinIN2, MotorDriverType driverType = DRIVER_L298N);

   // --- Methods ---
   void setSpeed(int pwmVal); // Speed value (0-255)
   unsigned short getSpeed();
   void forward();
   void forwardFor(unsigned long delay, CallBackFunction callback);
   void forwardFor(unsigned long delay);
   void backward();
   void backwardFor(unsigned long delay, CallBackFunction callback);
   void backwardFor(unsigned long delay);
   void controlBySpeed(int pwmVal); // Control direction and speed (-255 to 255)
   void run(AlashMotorControl::Direction direction);
   void runFor(unsigned long delay, AlashMotorControl::Direction direction);
   void runFor(unsigned long delay, AlashMotorControl::Direction direction, CallBackFunction callback);
   void stop();     // Coast stop (LOW/LOW on outputs)
   void HardStop(); // Brake stop (HIGH/HIGH on outputs)
   void reset();
   boolean isMoving();
   Direction getDirection();
   MotorDriverType getDriverType(); // Helper to check the driver type


private:
   byte _pinEnable; // Enable pin (-1 if not used, e.g., for TA6586 or jumpered L298N)
   byte _pinIN1;
   byte _pinIN2;
   int _pwmVal; // Current speed (0-255)
   MotorDriverType _driverType; // Store the type of driver being used

   // State variables
   unsigned long _lastMs;
   boolean _canMove;
   boolean _isMoving;
   AlashMotorControl::Direction _direction;

   // Internal helper
   static void fakeCallback();
};

#endif // AlashMotorControl_h