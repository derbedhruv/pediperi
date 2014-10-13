String inputString="", lat="", longit="";
boolean acquired = false, breakOut = false;

const int ledPin =  13;      // the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)


void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
}

void loop()
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    if (breakOut == false) {
      digitalWrite(ledPin, ledState);
    } else {
      digitalWrite(ledPin, LOW);      // stop that shit
      Serial.println("stopped");
    }
  }
}


void serialEvent() {
  // breakOut = false;
  if (Serial.available()) {
    char inChar = (char)Serial.read(); 
    // adding an 'x' for breaking out of any for loop..
    if (inChar == ',') {  // normal, previous function
      breakOut = false;
      // Serial.println(inputString);
      lat = inputString;
      Serial.println(lat);
      // reset that shit
      inputString = "";
    } else {
      
      if (inChar == '\n') {
        breakOut = false;
        longit = inputString;
        Serial.println(longit);
        
        if (longit[0] == 'x') {
          breakOut = true;  // break out of the loops yo
          Serial.println("breaking out");
          // break;
        }
        // lightHerUp(lat, longit);  // write to arduino
        // reset that shit
        inputString = "";
        
        
        
      } else {
        inputString += inChar;
      }
    }
  }
}
