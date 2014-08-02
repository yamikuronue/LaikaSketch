//For testing servos on Laika

#include <Servo.h> 
 
Servo tail;  // create servo object to control a servo
Servo leftEar;
Servo rightEar;
 
int pos = 0;    // variable to store the servo position 
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  leftEar.attach(10);
  rightEar.attach(11);
  leftEar.write(0);
  rightEar.write(180);
  
  tail.attach(3);  
  tail.write(0);
  delay(5);
} 
 
 
void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  if (val < 700) {
    val = map(val, 0, 700, 5, 30);     // scale it to use it with the servo (value between 0 and 180) 
    doSweep(val);
  }
  
  
} 

void doSweep(int delayval) {
  leftEar.write(0);
  rightEar.write(180);
  
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    tail.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(delayval);                       // waits 15ms for the servo to reach the position 
  } 
  
  leftEar.write(180);
  rightEar.write(0);
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    tail.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(delayval);                       // waits 15ms for the servo to reach the position 
  } 
}
