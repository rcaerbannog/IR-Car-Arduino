#include <IRremote.h>

const int IR_SEND_PIN = 3;
void setup() {
  IrSender.begin(IR_SEND_PIN, DISABLE_LED_FEEDBACK);
  //pinMode(12, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int xPos = analogRead(A1)/32; //Scale from 0 to 32 (5 bits). Centers at 15.
  int yPos = analogRead(A0)/16; //Scale from 0 to 64 (6 bits). Centers at 32.
  //int buttonState = digitalRead(12);

  
  Serial.print("X: ");
  Serial.print(xPos);
  Serial.print(" , Y: ");
  Serial.print(yPos);
  Serial.print(" , button: ");
  //Serial.print(buttonState);
  Serial.println();
  

  /*
  //RC5: 5 address bits, 6 command bits
  int sAddress = 0x0F;
  int sCommand = 0x1B;
  IrSender.sendRC5(sAddress, sCommand, 0, true);  //0 repeats. Delay next send by at least 5 ms.
  */
  
  IrSender.sendRC5(xPos, yPos, 0, true);
  delay(20);
}
