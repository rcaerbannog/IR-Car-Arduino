#define CH1 11
#define CH2 6

const int RECV_PIN = 13;
const int enable12_pin = 10;
const int enable34_pin = 9;
const int input1_pin = 3;
const int input2_pin = 2;
const int input3_pin = 4;
const int input4_pin = 5;

const double bias = 1.1;

//int prev_on_off_state = LOW;
//boolean isOn = false;

int controlSpeed = 0;
int controlSteering = 0;
int motorLSpeed = 0;
int motorRSpeed = 0;



// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void motorControl(){
  //Serial.print(motorLSpeed);
  //Serial.print(" ");
  //Serial.println(motorRSpeed);
  
  //left motor: enable12. 2 high is forwards
  if (motorLSpeed > 0){
    digitalWrite(input1_pin, LOW);
    digitalWrite(input2_pin, HIGH);
  }
  else if (motorLSpeed < 0){
    digitalWrite(input1_pin, HIGH);
    digitalWrite(input2_pin, LOW);
  }
  else{
    digitalWrite(input1_pin, HIGH);
    digitalWrite(input2_pin, HIGH);
  }
  analogWrite(enable12_pin, constrain(abs(motorLSpeed), 0, 255));
  
  //right motor: enable34. 4 high is forwards
  if (motorRSpeed > 0){
    digitalWrite(input3_pin, LOW);
    digitalWrite(input4_pin, HIGH);
  }
  else if (motorRSpeed < 0){
    digitalWrite(input3_pin, HIGH);
    digitalWrite(input4_pin, LOW);
  }
  else{
    digitalWrite(input3_pin, HIGH);
    digitalWrite(input4_pin, HIGH);
  }
  analogWrite(enable34_pin, constrain(abs(motorRSpeed), 0, 255));
}

void setup() {
  //Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(enable12_pin, OUTPUT);
  pinMode(enable34_pin, OUTPUT);
  pinMode(input1_pin, OUTPUT);
  pinMode(input2_pin, OUTPUT);
  pinMode(input3_pin, OUTPUT);
  pinMode(input4_pin, OUTPUT);

  analogWrite(enable12_pin, 0);
  digitalWrite(input1_pin, HIGH);
  digitalWrite(input2_pin, LOW);
  analogWrite(enable34_pin, 0);
  digitalWrite(input3_pin, HIGH);
  digitalWrite(input4_pin, LOW);
}

void loop() {
  controlSteering = readChannel(CH1, -255, 255, 0);
  controlSpeed = readChannel(CH2, -255, 255, 0);
  if (abs(controlSteering) < 32) controlSteering = 0;
  if (abs(controlSpeed) < 32) controlSpeed = 0;
  motorLSpeed = (int)(bias*controlSpeed) + controlSteering;
  motorRSpeed = controlSpeed - controlSteering;
  motorControl();
  delay(50);
  
}
