#include <Arduino.h>
#include <IRRemote.h>

#define BUTTON 18

IRCode IRcode;

bool isThereCode = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON, INPUT_PULLDOWN);
  IRcode.begin();
}

void loop() {
  if(digitalRead(BUTTON) == 1 && isThereCode == 0){
    IRcode.IRrecStart();
    Serial.print("Waiting code:");
    for(int i = 0 ; i < 10 ; i++){
      Serial.print(".");
      delay(500);
    }
    IRcode.IRrecStop();
    Serial.println("Aquisition end.");
    IRcode.printPulseWidthVector();
    IRcode.printPulseWidthVectorinBinary();
    isThereCode = 1;
  }
  if(digitalRead(BUTTON) == 1 && isThereCode == 1){
    Serial.println("Sending data");
    IRcode.IRsendRaw();
  }
}


