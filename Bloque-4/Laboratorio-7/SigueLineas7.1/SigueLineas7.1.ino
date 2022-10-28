#include <Servo.h>
Servo servoLeft;
Servo servoRight;
int pinServoLeft = 8;
int pinServoRight = 9;

void setup(){
  servoLeft.attach(pinServoLeft);
  servoRight.attach(pinServoRight);
}

void loop(){
    // Atrás
    servoLeft.write(180); // Velocidad Máxima
    servoRight.write(0);
    delay(3000);
    servoLeft.write(100); // Próximo a 90, despacio
    servoRight.write(80);
    delay(3000);

    servoLeft.write(90); // Detener
    servoRight.write(90);
    delay(3000);

    // Adelante
    servoLeft.write(80); // Próximo a 90, despacio
    servoRight.write(100);
    delay(3000);
    servoLeft.write(0); // Velocidad Máxima
    servoRight.write(180);
    delay(3000);
}