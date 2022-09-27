#include <IRremote.h>

const int on_off_pin = 13;
const int RECV_PIN = 11;
const int enable12_pin = 10;
const int enable34_pin = 9;
const int input1_pin = 3;
const int input2_pin = 2;
const int input3_pin = 4;
const int input4_pin = 5;


int prev_on_off_state = LOW;
boolean isOn = false;

int controlSpeed = 0;
int controlSteering = 0;
int motorLSpeed = 0;
int motorRSpeed = 0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(on_off_pin, INPUT);
  pinMode(enable12_pin, OUTPUT);
  pinMode(enable34_pin, OUTPUT);
  pinMode(input1_pin, OUTPUT);
  pinMode(input2_pin, OUTPUT);
  pinMode(input3_pin, OUTPUT);
  pinMode(input4_pin, OUTPUT);

  //analogWrite(enable12_pin, 150);
  digitalWrite(input1_pin, HIGH);
  digitalWrite(input2_pin, LOW);
  //analogWrite(enable34_pin, 150);
  digitalWrite(input3_pin, HIGH);
  digitalWrite(input4_pin, LOW);

  IrReceiver.begin(RECV_PIN);
}

void motorControl(){
  //left motor: enable12. 1 high is forwards
  if (motorLSpeed > 0){
    digitalWrite(input1_pin, HIGH);
    digitalWrite(input2_pin, LOW);
  }
  else if (motorLSpeed < 0){
    digitalWrite(input1_pin, LOW);
    digitalWrite(input2_pin, HIGH);
  }
  else{
    digitalWrite(input1_pin, HIGH);
    digitalWrite(input2_pin, HIGH);
  }
  analogWrite(enable12_pin, constrain(abs(motorLSpeed), 0, 255));
  
  //right motor: enable34. 3 high is forwards
  if (motorRSpeed > 0){
    digitalWrite(input3_pin, HIGH);
    digitalWrite(input4_pin, LOW);
  }
  else if (motorRSpeed < 0){
    digitalWrite(input3_pin, LOW);
    digitalWrite(input4_pin, HIGH);
  }
  else{
    digitalWrite(input3_pin, HIGH);
    digitalWrite(input4_pin, HIGH);
  }
  analogWrite(enable34_pin, constrain(abs(motorRSpeed), 0, 255));
}

void loop() {
  // On/off switch
  int on_off_state = digitalRead(on_off_pin);
  if (on_off_state != prev_on_off_state && on_off_state == HIGH){
    isOn = !isOn;
    if (isOn){
      analogWrite(enable12_pin, 150);
      analogWrite(enable34_pin, 150);
    }
    else{
      analogWrite(enable12_pin, 0);
      analogWrite(enable34_pin, 0);
      controlSpeed = 0;
      controlSteering = 0;
      motorLSpeed = 0;
      motorRSpeed = 0;
    }
    prev_on_off_state = on_off_state;
  }
  else if (on_off_state != prev_on_off_state) prev_on_off_state = on_off_state;

  if (!isOn) return;

  //Receiving remote command input
  if (IrReceiver.decode()){
    controlSteering = IrReceiver.decodedIRData.address - 15;  //Steering, 0-31, centered at 15. x-axis control
    controlSpeed = IrReceiver.decodedIRData.command - 32;  //Speed, 0-63, centered at 32. y-axis control
    IrReceiver.resume();
    Serial.print(controlSteering);
    Serial.print(" , ");
    Serial.println(controlSpeed);
    
    //Determine the appropriate motor speeds
    motorLSpeed = 8*controlSpeed + 8*controlSteering;
    motorRSpeed = 8*controlSpeed - 8*controlSteering;
    //motorLSpeed = 8*controlSpeed;
    //motorRSpeed = 8*controlSpeed;

    motorControl();
  }

  delay(50);
  
}
