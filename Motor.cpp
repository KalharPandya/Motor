#include "Motor.h"

Motor::Motor(int pwm, int dir1,int dir2){
    randomSeed(10);
    Motor::dir1 = dir1;
    Motor::dir2 = dir2;
    Motor::pwm->attach(pwm);
    pinMode(dir1,OUTPUT);
    pinMode(dir2,OUTPUT);
}

void Motor::setEncoder(UniversalEncoder *enc){
    Motor::virtualMode = false;
    Motor::encoder = enc;
}

void Motor::setEncoder(int en1,int  en2,int dir){
    Motor::virtualMode = false;
    Motor::encoder->init(en1, en2, dir);
}

void Motor::invertDirection(int direction_offset){
    Motor::direction_offset = direction_offset;
    Motor::encoder-> directional_offset=-(direction_offset);
}

void Motor::setPWM(int pwm){
    getVirtualReadings();
    pwm*=Motor::direction_offset;
    Motor::pwm->write(pwm);
    errorPWM = erroredPWM(pwm);
    // Serial.println(errorPWM);
    if(pwm > 0){
        forward();
    }
    else if(pwm<0){
        backward();
    }
    else{
        stop();
    }
}

void Motor::forward(){
    digitalWrite(dir1, HIGH);
    if(dir2>=0)
        digitalWrite(dir2, LOW);
}

void Motor::backward(){
    digitalWrite(dir1, LOW);
    if(dir2>=0)
        digitalWrite(dir2, HIGH);
}

void Motor::stop(){
    digitalWrite(dir1, LOW);
    if(dir2>=0)
        digitalWrite(dir2, LOW);
    Motor::pwm->write(1);
}

long Motor::getReadings(){
    if(Motor::virtualMode){
        return Motor::getVirtualReadings();
    }
    return Motor::encoder->getReadings();
}

void Motor::setReadings(long readings){
    return Motor::encoder->setReadings(readings);
}

void Motor::reset(){
    Motor::encoder->reset();
    Motor::stop();
}
int Motor::erroredPWM(int pwm){
    int max = pwm * Motor::virtualError;
    int randomNumber =random(-100,100); 
    int error = map(randomNumber,-100,100,-max, max);
    return pwm + error;
}
long Motor::getVirtualReadings(){
    Motor::readings += 0.025 * (millis() - Motor::prevTime) * Motor::errorPWM;
    Motor::prevTime = millis();

    return Motor::readings;
}
