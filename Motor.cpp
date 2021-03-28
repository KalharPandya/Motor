#include "Motor.h"

Motor::Motor(int pwm, int dir1,int dir2){
    Motor::dir1 = dir1;
    Motor::dir2 = dir2;
    Motor::pwm->attach(pwm);
    pinMode(dir1,OUTPUT);
    pinMode(dir2,OUTPUT);
}

void Motor::setEncoder(UniversalEncoder *enc){
    Motor::encoder = enc;
}

void Motor::setEncoder(int en1,int  en2,int dir){
    Motor::encoder->init(en1, en2, dir);
}

void Motor::setPWM(int pwm){
    if(pwm > 0){
        forward();
        Motor::pwm->write(pwm);
    }
    else if(pwm<0){
        backward();
        Motor::pwm->write(pwm);
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
    return Motor::encoder->getReadings();
}
void Motor::setReadings(long readings){
    return Motor::encoder->setReadings(readings);
}
void Motor::reset(){
    Motor::encoder->reset();
    Motor::stop();
}
