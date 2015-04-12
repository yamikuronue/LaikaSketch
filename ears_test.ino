#include <Adafruit_SoftServo.h>

#define LEFT 1
#define RIGHT 0
#define SWITCH 2
 
Adafruit_SoftServo leftEar;
Adafruit_SoftServo rightEar;
 
void setup() 
{ 
  leftEar.attach(LEFT);
  rightEar.attach(RIGHT);
} 
 
 
void loop() 
{ 
 doSweep(300);
} 

void doSweep(int delayval) {
  leftEar.write(0);
  delay(30);
  rightEar.write(160);
  
  delay(delayval);  
  
  leftEar.write(160);
  delay(30);
  rightEar.write(0);
  
  delay(delayval);
  
  leftEar.refresh();
  rightEar.refresh();
}
