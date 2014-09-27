#include <ctype.h>

String inputString, lat, longit;
boolean acquired = false;

void setup() {
  // serial dude
  Serial.begin(9600);
  
  // SET THE PINS WHICH WILL BE USED
  // we set the longitudes as OUTPUT
  for (int i=2; i<=10; i++) {
    pinMode(i, OUTPUT);
  }
  
  // we then set the latitudes as output
  for (int m=22; m<=52; m++) {
    pinMode(m, OUTPUT);
  }
  /*
  step 1: set the latitude to be HIGH
  digitalWrite(5, HIGH);
  
  step 2: set all the longitudes to be HIGH, so that everything's shut off
  for (int j=22; j<=52; j++) {
    digitalWrite(j, HIGH);
  }
  
  step 3: set the longitude which you need to be on, LOW. then you have a single LED on.
  digitalWrite(27, LOW);
  /**/ 
}

void lightHerUp(String latitude, String longitude) {
   // this is a special function.
   // for single LEDs, the arguments shall be numbers in the range ((2, 10), (22, 46))
   // for hemispheres, the inputs will be ((h), [n,e,w,s]) corresponding to the 4 hemispheres possible
   // for quadrants, the inputs will be ((q), [1,2,3,4]) corresponding to the 4 quadrants possible
   // all LEDs will flash for a particular period of time and then cut off.
   
   // we start by resetting all the LEDs
   // step 1: turn OFF all latitudes..
       for (int h=2; h<=10; h++) {
         digitalWrite(h, LOW);
       }
   // step 2: set all the longitudes to be HIGH, so that everything's shut off
       for (int j=22; j<=52; j++) {
         digitalWrite(j, HIGH);
       }
   
   // first check if the latitude value is a number or not..
   if (isdigit(latitude[0]) == 1) {  // the latitude will only be (2,10) so that's cool, it's only one char
       // this is the case for a single LED
       // step 1: set the latitude to be HIGH
       digitalWrite(latitude.toInt(), HIGH);
  
       // step 2: set the longitude which you need to be on, LOW. then you have a single LED on.
       digitalWrite(longitude.toInt(), LOW);
       
     } else {
     // Serial.println(latitude[0]);
     // we deal with 2 cases: hemispheres and quadrants
     switch(latitude[0]) {
       case 'h': {
         // Serial.println("hemisphere");
         // we then switch through WHICH hemisphere
         switch(longitude[0]){
           case 'l': {
             // LEFT hemisphere.. turn on U to X and A to I.
             
             break;
           }
           case 'r': {
             // LEFT hemisphere.. turn on I to T.
             
             break;  
           }
         }
         break;
       }
       case 'q': {
         // Serial.println("quadrant");
         break;
       }
     }
     
   }
}

void loop() {
  if (acquired == true) {
     // Serial.print("started... ");
     lightHerUp(lat, longit);
     acquired = false;
  }
}

void serialEvent() {
  // this is where the user can enter the LED they want to be put on.. and that's what'll happen
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    
    if (inChar == ',') {
      // Serial.println(inputString);
      lat = inputString;
      // reset that shit
      inputString = "";
    } else {
      if (inChar == '\n') {
        longit = inputString;
        // Serial.println(inputString);
        // reset that shit
        inputString = "";
        acquired = true;
      } else {
        inputString += inChar;
      }
    }
  }
}
