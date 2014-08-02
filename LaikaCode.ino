
/* Code for controlling Laika Leonne accessories v 1.0 -- two ears and tail.
Written by Yamikuronue*/
#include <Servo.h> 
 
Servo tail;  // create servo object to control a servo
Servo leftEar;
Servo rightEar;
 
int pos = 0;    // variable to store the tail position 
int potpin = 0;  // analog pin used to connect the potentiometer
int potval;    // variable to read the value from the analog pin 
int threshold = 600; //Maximum value to allow sweeping
                    //Remember that the higher the value, the slower the tail motion
                    //so above a certain value, we just treat it as stopped

int togglePin; //Holds the pin for the toggle for the interrupt
volatile int togglePos; //Position of the toggle, high vs low

//Sin wave lookup table computed by Rednaxela
const int sweepLUT[] = {
544,544,545,545,546,548,549,551,553,555,558,561,564,568,572,576,580,585,589,
595,600,606,612,618,624,631,638,645,653,660,668,677,685,694,703,712,721,731,
741,751,761,772,782,793,804,816,827,839,851,863,875,888,901,914,927,940,953,
967,980,994,1008,1022,1036,1051,1065,1080,1095,1109,1124,1139,1155,1170,1185,
1201,1216,1232,1247,1263,1279,1295,1311,1327,1343,1359,1375,1391,1407,1423,
1440,1456,1472,1488,1504,1521,1537,1553,1569,1585,1601,1617,1633,1649,1665,
1681,1697,1712,1728,1743,1759,1774,1789,1805,1820,1835,1849,1864,1879,1893,
1908,1922,1936,1950,1964,1977,1991,2004,2017,2030,2043,2056,2069,2081,2093,
2105,2117,2128,2140,2151,2162,2172,2183,2193,2203,2213,2223,2232,2241,2250,
2259,2267,2276,2284,2291,2299,2306,2313,2320,2326,2332,2338,2344,2349,2355,
2359,2364,2368,2372,2376,2380,2383,2386,2389,2391,2393,2395,2396,2398,2399,
2399,2400,2400};
 
void setup() 
{ 
  attachInterrupt(togglePin, toggleEars, CHANGE);
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
  potval = analogRead(potpin);   // reads the value of the potentiometer (value between 0 and 1023) 
  if (potval < threshold) {
    potval = map(potval, 0, threshold, 5, 30);   // scale it to use it with the servo (value between 0 and 180) 
    doSweep(potval);
  } else {
    //stop in neutral position -- easier to sit that way
    tail.write(90);                     
  }
} 

void doSweep(int delayval) {
  //Sweep left to right
  for(pos = 0; pos < 180; pos += 1)  
  {                                
    tail.write(sweepLUT[pos]);            
    delay(delayval);                       
  } 
  
  //Sweep right to left
  for(pos = 180; pos>=1; pos-=1)    
  {                                
    tail.write(sweepLUT[pos]);              
    delay(delayval);                      
  } 
}

void toggleEars() {
    togglePos = DigitalRead(togglePin);
    if(togglePos) {
      leftEar.write(0);
      rightEar.write(180);
    } else {
      leftEar.write(180);
      rightEar.write(0);
    }
}
