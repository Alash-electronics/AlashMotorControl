/*
 * TA6586_Demo.ino
 *
 * Basic demonstration of the AlashMotorControl library using the
 * TA6586 (ZK-5AD) motor driver.
 *
 * Connections:
 * - Arduino Pin 5 --> Motor Driver IN1
 * - Arduino Pin 6 --> Motor Driver IN2
 * - Motor Driver OUT1/OUT2 --> DC Motor
 * - Motor Driver VCC --> Motor Power Supply (+)
 * - Motor Driver GND --> Motor Power Supply (-) and Arduino GND
 *
 */

 #include <AlashMotorControl.h> // Use the base library

 // Define motor control pins
 const int MOTOR_IN1_PIN = 5; // Connect to TA6586 IN1
 const int MOTOR_IN2_PIN = 6; // Connect to TA6586 IN2
 
 // Create an instance of AlashMotorControl for the TA6586 driver
 // Use the 2-pin constructor and specify the driver type
 AlashMotorControl motor(MOTOR_IN1_PIN, MOTOR_IN2_PIN, DRIVER_TA6586);
 
 void setup() {
   Serial.begin(9600); // Optional: for debugging output
   Serial.println("TA6586 Motor Demo");
 
   // Set the desired speed (0-255).
   // For TA6586, this value is used in analogWrite() during forward/backward calls.
   motor.setSpeed(200);
   Serial.print("Motor speed set to: ");
   Serial.println(motor.getSpeed()); // Will show 0 until motor moves
 
   Serial.println("Running Forward...");
   motor.forward();
   Serial.print("Current Speed: "); Serial.println(motor.getSpeed()); // Now shows speed
   Serial.print("Direction: "); Serial.println(motor.getDirection());
   delay(2000); // Run forward for 2 seconds
 
   Serial.println("Running Backward...");
   motor.backward();
    Serial.print("Current Speed: "); Serial.println(motor.getSpeed());
    Serial.print("Direction: "); Serial.println(motor.getDirection());
   delay(2000); // Run backward for 2 seconds
 
   Serial.println("Stopping Motor (Coast)...");
   motor.stop();
    Serial.print("Current Speed: "); Serial.println(motor.getSpeed()); // Should be 0
    Serial.print("Direction: "); Serial.println(motor.getDirection());
   delay(1000);
 
   Serial.println("Running Forward with controlBySpeed (+150)...");
   motor.controlBySpeed(150); // Positive value -> forward
   delay(2000);
 
   Serial.println("Running Backward with controlBySpeed (-150)...");
   motor.controlBySpeed(-150); // Negative value -> backward
   delay(2000);
 
   Serial.println("Stopping Motor (Brake) with HardStop...");
   motor.HardStop();
   delay(1000);
 
 
   Serial.println("Demo Finished. Motor stopped.");
 }
 
 void loop() {
   // Nothing needed here for this basic demo
   // You could add more complex logic, e.g., using runFor()
 }