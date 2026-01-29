#include <SoftwareSerial.h>

#define PIN 5

String output = "";  

SoftwareSerial uno(PIN, PIN);

void setup() {
  Serial.begin(9600);
  uno.begin(9600);
  pinMode(PIN, INPUT_PULLUP); // Start in receive mode
}

void loop() {
  if (uno.available() > 0) {
    pinMode(PIN, INPUT_PULLUP); // Switch back to receive mode
   // delay(100); 

    String input1 = uno.readStringUntil('\n'); // Read data until ‘\n’ is received
    input1.trim();


    // output = ""; 

    // if (input1.equals("kku")) {
    //   output = "ESE";
    // } 
    // else if (input1.equals("suv")) {
    //   output = "CAR";
    // }
    // else if (input1.equals("en")) {
    //   output = "gear";
    // }
    // else if (input1.equals("hi")) {
    //   output = "hello";
    // }

    pinMode(PIN, OUTPUT); // Switch to transmit mode
   // delay(100);
    //uno.println(output); 
    uno.println(input1); // Send the message back to board A
   // delay(100);
    pinMode(PIN, INPUT_PULLUP);// Start in receive mode
  }
}

