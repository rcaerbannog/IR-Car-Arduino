# IR-Car-Arduino
Arduino car controlled by infrared RX/TX using the IRremote library. A small project I did in summer of 2021 (just before I went to UBC) and returned to in summer 2022.

In summer 2021, I used the IRremote library in Arduino to send and receive commands, and I used this ability to control a car built from my Arduino kit. The speed of two motors was controlled with an L293D half H-bridge IC to move and turn the robot. I had no gearbox however, so it was very weak.

In summer 2022, I picked up a chassis with gearboxes to amplify the motor torque and allow the car to move substantially under its own power. Unfortunately, my IR sensor broke, so I swapped in the radio receiver from my RC planes. Since this receiver is meant to control servos, the output is a PWM signal that can be read manually from the Arduino's PWM pins. The working car can be viewed here: https://youtu.be/PUpz7kgrG0M
