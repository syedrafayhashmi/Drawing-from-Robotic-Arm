#include <math.h>
#include <Servo.h>

//for radians to degree conversion
const float radTodegree = 180 / PI;

#define ARMLENGTH 100 //arm length

Servo servo1, servo2;

int posX=0,posY=0;

void setup() {
  servo1.attach(7);
  servo2.attach(8);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0)
  {
    posX = Serial.parseInt();
    posY = Serial.parseInt();

  }
  Serial.print(posX);
  Serial.print(",");
  Serial.println(posY);
  armTo(posX,posY);
}

//calculate new angles based on a desired x,y
void armTo(float x, float y) {
  float h = sqrt(square(x) + square(y));
  //calculates angles based on desired point
  float a1 = (getAngle(ARMLENGTH, ARMLENGTH, h) + atan2(y, x));
  float a2 = (getAngle(h, ARMLENGTH, ARMLENGTH));
  moveServo(a1, a2);
}

void moveServo(float a1, float a2) {
  int deg1=constrain((PI-a1) * radTodegree,0,180);
  int deg2=180-constrain(a2 * radTodegree,0,180);
  //180-deg so servo moves from right to left
  servo1.write(deg1);
  servo2.write(deg2);
//  Serial.print(deg1);
//  Serial.print(",");
//  Serial.println(deg2);
  delay(500);
}

float getAngle(float a, float b, float c) {
  return acos((square(b) + square(c) - square(a)) / (2 * b * c));
}
