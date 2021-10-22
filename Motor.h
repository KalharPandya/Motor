#ifndef Motor_h
#define Motor_h
#include<Arduino.h>
#include<UniversalPWM.h>
#include<UniversalEncoder.h>

class Motor{
    public:
        bool virtualMode = false;
        int errorPWM = 0;
        double virtualError = 0.2;
        long prevTime = 0;
        long double  readings = 0;
        int dir1, dir2, direction_offset = 1;
        UniversalEncoder *encoder = new UniversalEncoder();
        UniversalPWM *pwm = new UniversalPWM();
        Motor(){
            
        }
        Motor(int pwm, int dir1,int dir2=-1);
        void setEncoder(UniversalEncoder *encoder);
        void setEncoder(int en1,int  en2,int dir = 1);
        void invertDirection(int direction_offset = -1);
		void setPWM(int pwm);
        int erroredPWM(int pwm);
		void forward();
		void stop();
		void backward();
		long getReadings();
		void setReadings(long readings);
		void reset();
        long getVirtualReadings();
};

#endif
