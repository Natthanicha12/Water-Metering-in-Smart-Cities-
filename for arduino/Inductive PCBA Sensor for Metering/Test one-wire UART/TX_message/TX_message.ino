#include <SoftwareSerial.h>

#define PIN 5

SoftwareSerial uno(PIN, PIN);

void setup() {
  Serial.begin(9600);
  uno.begin(9600);
  pinMode(PIN, INPUT_PULLUP); // Start in receive mode
}

void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n'); // Read Serial Monitor input until ‘\n’
    pinMode(PIN, OUTPUT); // Switch to transmit mode
    uno.println(message); // Send the message back to board B
    //delay(100);
    pinMode(PIN, INPUT_PULLUP); // Switch back to receive mode
  }

  if (uno.available() > 0) {
    //delay(100); 
    String message = uno.readStringUntil('\n'); // Read message from board B
    Serial.println("Received from B: " + message); 
  }
}
