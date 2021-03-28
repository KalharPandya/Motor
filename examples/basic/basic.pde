#include <Motor.h>
UniversalEncoder myEnc(2,3,1);//Create Encoder Object from its pin(En1, En2 , DirectionalOffset)
Motor m1(9,5,6);//Create Motor Object (Pwm pin, Dir pin1, Dir pin2 (Optional))
Motor m2(10,8); //For drivers with single direction pin
void setup() {
  // put your setup code here, to run once:
  
  m1.setEncoder(&myEnc);//Pass encoder object to m1

  m1.setEncoder(2,3,-1);//You can also pass Encoder pins and offsets(En1, En2 , DirectionalOffset)

  m1.setPWM(200);//Forward 200 PWM
  m1.setPWM(-200);//Backward 200 PWM
  
  m1.setPWM(0);//Stop

}

void loop() {
  Serial.print("Motor Readings");
  Serial.println(m1.getReadings());
  
  Serial.print("Motor Reseting");
  m1.reset();

  Serial.print("Motor SetReadings");
  m1.setReadings(200);

}