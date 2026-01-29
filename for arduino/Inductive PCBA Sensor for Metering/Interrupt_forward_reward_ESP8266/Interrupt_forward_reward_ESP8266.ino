const int inputPin = 14; // Define the input pin for pulse counting        //D5
const int inputPin1 = 12; //D6
volatile unsigned long pulseCount = 0; // Initialize pulse count variable
unsigned long Time_1  ;
unsigned long Time_2 ;
unsigned long Time_3 ;
unsigned long Time_total ;
unsigned long Time_positive ;
unsigned long Time_zero  ;
float frequency;
int x = 0;
int y = 0;
int z = 0;

int count_F = 0;
int count_R = 0;

void setup() {
  pinMode(inputPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(inputPin), pulseCounting, CHANGE); // Attach interrupt to the input pin
  attachInterrupt(digitalPinToInterrupt(inputPin1), pulseCounting1, CHANGE);

  Serial.begin(9600); // Initialize serial communication
  Serial.println(" hello ");
}

void loop() {

  if(x == 1 && y == 1 && z==1 ){

    Time_positive = Time_3 - Time_1 ;
    Time_zero = Time_2 - Time_3;
    Time_total = Time_positive + Time_zero;

    if( pulseCount <= 2){

      if(digitalRead(inputPin)){
        Serial.println("-----------------------");
        Serial.println("Forward pulse");
        Serial.println("-----------------------");

        count_F++;
        if(count_F == 10){
          Serial.println("count_F");
          count_F = 0;
        }

      }else if(digitalRead(inputPin1)){
        Serial.println("-----------------------");
        Serial.println("Reverse pulse");
        Serial.println("-----------------------");

        count_R++;
        if(count_R == 10){
          Serial.println("count_R");
          count_R = 0;
        }
      }

    Serial.println("======================");

    Serial.print("Time_positive : ");
    Serial.print(Time_positive);
    Serial.println(" ms ");

    Serial.print("Time_zero : ");
    Serial.print(Time_zero);
    Serial.println(" ms ");

    Serial.print("Time_total : ");
    Serial.print(Time_total);
    Serial.println(" ms ");
    
    Serial.println("======================");
    }

    pulseCount = 0;
    x = 0;
    y = 0;
    z = 0;

  }
}

ICACHE_RAM_ATTR void pulseCounting() {
  if (digitalRead(inputPin) == HIGH) {

    pulseCount++;
    Serial.print("Pulse Count: ");
    Serial.println(pulseCount);

    if(pulseCount == 1){
      x = 1;
      Time_1 = millis();
      //Serial.print("Time1 = ");
      //Serial.println(Time_1);
    } else if (pulseCount == 2) {
      y = 1;
      Time_2 = millis();
      //Serial.print("Time2 = ");
      //Serial.println(Time_2);
      
    }
  }
    else {
    z = 1;
    Time_3 = millis();
  }
}

ICACHE_RAM_ATTR void pulseCounting1() {
  if (digitalRead(inputPin1) == HIGH) {

    pulseCount++;
    Serial.print("Pulse Count: ");
    Serial.println(pulseCount);

    if(pulseCount == 1){
      x = 1;
      Time_1 = millis();
      //Serial.print("Time1 = ");
      //Serial.println(Time_1);
    } else if (pulseCount == 2) {
      y = 1;
      Time_2 = millis();
      //Serial.print("Time2 = ");
      //Serial.println(Time_2);
      
    }
  }
    else {
    z = 1;
    Time_3 = millis();
  }
}

