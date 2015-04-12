#include <Adafruit_SoftServo.h>

#define LEFT 1
#define RIGHT 0
#define SWITCH 2
#define EARS_UP 1
#define EARS_DOWN 0
 
Adafruit_SoftServo leftEar;
Adafruit_SoftServo rightEar;

const int cooldownTime = 300; //ms
int lastPos;
 
void setup() 
{ 
   // Set up the interrupt that will refresh the servo for us automagically
  OCR0A = 0xAF;            // any number is OK
  TIMSK |= _BV(OCIE0A);    // Turn on the compare interrupt (below!)
  
  leftEar.attach(LEFT);
  rightEar.attach(RIGHT);
  
  pinMode(SWITCH, INPUT_PULLUP);
 // leftEar.write(0);
  
  earsSet(EARS_DOWN);
} 
 
 
void loop() 
{ 
 //Read switch
 int newPos = (digitalRead(SWITCH) == HIGH) ? EARS_UP : EARS_DOWN;
 
 //Determine if we need to move and, if so, move
 if (newPos != lastPos) earsSet(newPos);
} 

void earsSet(int pos) {
   switch (pos) {
     case EARS_DOWN:
       leftEar.write(0);
       rightEar.write(0);
       break;
     case EARS_UP:
       leftEar.write(180);
       rightEar.write(180);
       break;
   }
   lastPos = pos;
   delay(15);
}

volatile uint8_t counter = 0;
SIGNAL(TIMER0_COMPA_vect) {
  // this gets called every 2 milliseconds
  counter += 2;
  // every 20 milliseconds, refresh the servos!
  if (counter >= 20) {
    counter = 0;
    leftEar.refresh();
    rightEar.refresh();
  }
}
