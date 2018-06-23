#include <SoftwareSerial.h>
SoftwareSerial softSerial(0, 1); // RX, TX
//pinmode of L298N
int pinI1=2;//定义I1接口
int pinI2=3;//定义I2接口
int pinI3=4;//定义I3接口
int pinI4=5;//定义I4接口
int ENA=10;  //change speed
int ENB=11;    //change speed
int trigR1=8; // emit
int echoR1=9;//get
int trigL1=7; // emit
int echoL1=6;//get
int trigF=12; // emit
int echoF=A0;//get
const int speed=50; //forward speed

int storePin[3][2];
int detectAr[3];
int dir;

const int Fnum=0;
const int R1num=1;
const int L1num=2;
const int trigNum=0;
const int echoNum=1;
const int stopForwardDis=5;
const int LimDis=3;
const int turnTime=800;

void setup(){
    softSerial.begin(9600);
    Serial.begin(9600);
    pinMode(pinI1,OUTPUT);
    pinMode(pinI2,OUTPUT);
    pinMode(pinI3,OUTPUT);
    pinMode(pinI4,OUTPUT);
    pinMode(ENA,OUTPUT);
    pinMode(ENB,OUTPUT);
    pinMode(trigR1,OUTPUT);
    pinMode(echoR1,INPUT);
    pinMode(trigL1,OUTPUT);
    pinMode(echoL1,INPUT);
    pinMode(trigF,OUTPUT);
    pinMode(echoF,INPUT);

    //init
    storePin[Fnum][trigNum] = trigF;
    storePin[Fnum][echoNum] = echoF;
    storePin[R1num][trigNum] = trigR1;
    storePin[R1num][echoNum] = echoR1;
    storePin[L1num][trigNum] = trigL1;
    storePin[L1num][echoNum] = echoL1;
}
void range(){
    int trig;
    int echo;
    /*switch(num){
        case Fnum:
            trig=trigF;
            echo=echoF;
            break;
        case R1num:
            trig=trigR1;
            echo=echoR1;
            break;
        case L1num:
            trig=trigL1;
            echo=echoL1;
            break;        
    }*/
    for (int i = 0; i < 3; i++){
        trig = storePin[i][0];
        echo = storePin[i][1];
        digitalWrite(trig,LOW);
        delayMicroseconds(2);
        digitalWrite(trig,HIGH);
        delayMicroseconds(20);
        digitalWrite(trig,LOW);
        int distance = pulseIn(echo,HIGH); //读取高电平时间
        distance = distance/58; // cm
        detectAr[i] = distance;
    }

}


void getDir(){
    char s = softSerial.read();
    dir = s;
}

void back(){
    Serial.print("back\n");
    analogWrite(ENA,70);
    analogWrite(ENB,70);
    digitalWrite(pinI4,HIGH);
    digitalWrite(pinI3,LOW);
    digitalWrite(pinI1,HIGH);
    digitalWrite(pinI2,LOW);
}
void forward(){
    Serial.print("forward\n");
    analogWrite(ENA,70);
    analogWrite(ENB,70);
    digitalWrite(pinI4,LOW);//使直流电机（右）逆时针转
    digitalWrite(pinI3,HIGH);
    digitalWrite(pinI1,LOW);//使直流电机（左）顺时针转
    digitalWrite(pinI2,HIGH);
}
void left(){
    Serial.print("left\n");
    analogWrite(ENA,90);
    analogWrite(ENB,100);
    digitalWrite(pinI4,LOW);//使直流电机(右)逆时针转
    digitalWrite(pinI3,HIGH);
    digitalWrite(pinI1,HIGH);//使直流电机(左)逆时针转
    digitalWrite(pinI2,LOW); 
}
void litleft(){
    Serial.print("litleft\n");
    analogWrite(ENA,70);
    analogWrite(ENB,80);
    digitalWrite(pinI4,LOW);//使直流电机(右)逆时针转
    digitalWrite(pinI3,HIGH);
    digitalWrite(pinI1,HIGH);//使直流电机(左)逆时针转
    digitalWrite(pinI2,LOW); 
}
void right(){
    Serial.print("right\n");
    analogWrite(ENA,100);
    analogWrite(ENB,90);
    digitalWrite(pinI4,HIGH);//使直流电机(右)顺时针转
    digitalWrite(pinI3,LOW);
    digitalWrite(pinI1,LOW);//使直流电机(左)顺时针转
    digitalWrite(pinI2,HIGH);
}
void litright(){
    Serial.print("litright\n");
    analogWrite(ENA,80);
    analogWrite(ENB,70);
    digitalWrite(pinI4,HIGH);//使直流电机(右)顺时针转
    digitalWrite(pinI3,LOW);
    digitalWrite(pinI1,LOW);//使直流电机(左)顺时针转
    digitalWrite(pinI2,HIGH);
}
void stop(){
    Serial.print("stop\n");
    digitalWrite(pinI4,HIGH);//使直流电机(右)刹车
    digitalWrite(pinI3,HIGH);
    digitalWrite(pinI1,HIGH);//使直流电机左刹车
    digitalWrite(pinI2,HIGH);
}
//int judge = 0;
    unsigned long starttime;
    unsigned long stoptime;
    unsigned long looptime;
    int mark=0;
    int kazhu=0;
    int markkazhu=0;
   int markdis[300]={0};
    int marki =0;
    int init1=0;
    int init2=0;
void loop(){
    getDir();
    range();
    if((dir==49 || dir == 50)){
            
            //stop();
            //delay(5000);
           /* while(true){
              range();
              forward();
              delay(300);
              if(0<=detectAr[Fnum] && detectAr[Fnum]<=3)mark=1;
              break;
              }*/
            if (dir == 50){
                //back();
                //delay(2000);
                //stop();
                //delay(1000);
                forward();
                delay(1000);
                right();
                delay(turnTime);
                forward();
                delay(1000);
                Serial.println("turn left");
            }
            else if (dir == 49) {
                //back();
                //delay(2000);
                //stop();
                //delay(1000);
                forward();
                delay(1000);
                left();
                delay(turnTime);
               forward();
                delay(1000);
                Serial.println("turn right");
            }
    }
    if(0<=detectAr[R1num] && detectAr[R1num]<=3){
            litleft();
            /*if(markkazhu==0){init1=detectAr[R1num];  markkazhu=1;}
            if(markkazhu==1){init2=detectAr[R1num]; markkazhu=0;}*/
          /*  markdis[marki]=detectAr[R1num];
            marki++;*/
            Serial.println(detectAr[R1num]);
            Serial.println("\n");
            delay(300);
    }
   /* if (init1 == init2)kazhu++;*/
    if(0<=detectAr[L1num] && detectAr[L1num]<=3){
            litright();
            Serial.println(detectAr[L1num]);
            Serial.println("\n");
            delay(300);
    }
    
    if( 0<=detectAr[Fnum] && detectAr[Fnum]<=3){
                    back();
                    Serial.println(detectAr[Fnum]);
                    Serial.println("\n");
                    delay(2000);
            }
    /* if(kazhu==300){
        back();
                    Serial.println(detectAr[Fnum]);
                    Serial.println("\n");
                    delay(2000);
                    kazhu=0;
     }*/
    /* if(marki==300){
         for(int j=0;j<300;j++){
             if (markdis[0] != markdis[j])mark=1;
         }
         marki=0;
     }
     if (mark == 1){
         mark = 0;
          for(int j=0;j<300;j++){
             markdis[j]=0;
         }
         back();
                    Serial.println(detectAr[Fnum]);
                    Serial.println("\n");
                    delay(2000);
     }*/
     Serial.println(detectAr[Fnum]);
                    Serial.println("←\n");
    forward();
}
