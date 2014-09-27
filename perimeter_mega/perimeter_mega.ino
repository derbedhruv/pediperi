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
   // for hemispheres, the inputs will be ((h), [l,r]) corresponding to the 4 hemispheres possible
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
         // THis is the hemisphere case. Turn on all the latitudes..
         for (int p=2; p<=10; p++) {
           digitalWrite(p, HIGH);
         }
         // we then switch through WHICH hemisphere
         switch(longitude[0]){
           case 'l': {
             // LEFT hemisphere.. turn on U to X (31,37) and A to I (22,38).
             // first we put on 2*(11,19)
             for (int q=11; q<=19; q++) {
               digitalWrite(2*q, LOW);
             }
             // then we put on 2*(15,18)+1
             for (int r=15; r<=18; r++) {
               digitalWrite((2*r+1), LOW);
             }
             break;
           }
           case 'r': {
             // RIGHT hemisphere.. turn on J to T.. which is (40,52) in steps of 2 and (23, 29) in steps of 2
             // first we put on 2*(20,26)
             for (int q=20; q<=26; q++) {
               digitalWrite(2*q, LOW);
             }
             // then we put on 2*(11,14)+1
             for (int r=11; r<=14; r++) {
               digitalWrite((2*r+1), LOW);
             }
             break;  
           }
         }
         break;
       }
       case 'q': {
         // quadrants..
         // we start by putting the latitudes on
         for (int s=2; s<=10; s++) {
           digitalWrite(s, HIGH);
         }
         switch(longitude[0]) {
           // we shall go anticlockwise. "1" shall start from the bottom right. 
          case '1': {
            // the bottom right. O (50 to 52) to T (23 to 29).
            // then we put on 2*(11,14)+1
            for (int r=11; r<=14; r++) {
              digitalWrite((2*r+1), LOW);
              delay(1);
            }
            for (int q=25; q<=26; q++) {
               digitalWrite(2*q, LOW);
               delay(1);
             }
            break;
          } 
          case '2': {
            // the top right. I to N (38 to 48) 
            for (int q=19; q<=24; q++) {
               digitalWrite(2*q, LOW);
             }
            break;
          } 
          case '3': {
            // the top left. C to H. (26 to 36).
            for (int q=13; q<=18; q++) {
               digitalWrite(2*q, LOW);
               delay(1);
             }
            break;
          } 
          case '4': {
            // the bottom left. U to X (31 to 37), A to B (22, 24)
            // then we put on 2*(11,14)+1
            for (int r=15; r<=18; r++) {
              digitalWrite((2*r+1), LOW);
              delay(1);
            }
            for (int q=11; q<=12; q++) {
               digitalWrite(2*q, LOW);
               delay(1);
             }
            break;
          } 
         }
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
