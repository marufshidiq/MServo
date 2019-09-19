#include <MServo.h>

MServo myservo; // create servo object to control a servo

int potPin = A0; // Pin that connect to Potentiometer
int dirPin = 2;  // Pin to control the motor direction
int pwmPin = 3;  // Pin to control the motor speed

int minAngle = 0;
int maxAngle = 180;

int val = 0;
int diff = 1;

unsigned long previousMillis = 0;

void setup()
{
    myservo.attach(potPin, dirPin, pwmPin);        // Initialize pin
    myservo.setAngleConstrain(minAngle, maxAngle); // Set the maximum angle of servo
    myservo.setPotConstrain(0, 1023);              // Set the maximum analog value that refer to mechanical position of servo

    // myservo.reverse = true; // Enable this line if the rotation is wrong
    // myservo.setTolerance(4); // Set the tolerance of error for the target. Default = 6 => -3 to +3 degree

    val = minAngle;

    previousMillis = millis();
}

void loop()
{
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > 500){  // Update the angle value every 500 milliseconds
        val += diff;
        if(val == maxAngle){
            val-=1;
            diff = -1;
        }
        if(val == minAngle){
            val+=1;
            diff = 1;
        }
        previousMillis = currentMillis;
        myservo.write(val); // Set the servo angle to goal position
    }

    myservo.update(); // Update the servo rotation. This function must be called to ensure the servo is reach the goal position
    delay(50);
}