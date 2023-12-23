#include "VarSpeedServo.h"  //include VarSpeedServo library

VarSpeedServo RU;  //Right Upper
VarSpeedServo RL;  //Right Lower
VarSpeedServo LU;  //Left Upper
VarSpeedServo LL;  //Left Lower



int Echo = A4;  // 
int Trig =A3;  //  
int Distance = 0;
                                                     //vel(min), delay_Forward(max) = (5, 2000) 
const int vel = 40, vel_Back = 40;                   //vel(mid), delay_Forward(mid) = (20, 750) 
const int delay_Forward = 300, delay_Back = 450;    //vel(max), delay_Forward(min)= (256, 50)
                                                     //wonderful ---> (10, 700) (50, 500) (100, 100) (100, 300) (100, 500)
const int array_cal[4] = {1,80,90,92};   // Define the angular adjustment of servo (RU, RL, LU, LL )
const int delay_tim = 300;  //Delay 750ms
int RU_Degree = 0, LU_Degree = array_cal[2] + 5;

const int num1 = 8;
const int array_forward[num1][4] =  
{

    {0,-40,0,-20},        //forward
    {30,-40,30,-20},
    {30,0,30,0},
    {0,20,0,40},
    {-30,20,-30,40},
    {-30,0,-30,0},
    {-15,0,-15,0},
    {0,0,0,0},
};

const int num2 = 8; 
const int array_back[num2][4] =  
{     

    {0,-40,0,-20},        //Step-back
    {-30,-40,-30,-20},
    {-30,0,-30,0},
    {0,20,0,40},
    {30,20,30,40},
    {30,0,30,0},
    {15,0,15,0},
    {0,0,0,0},
};


void Servo_Init()
{
    RU.attach(3);   // Connect the signal wire of the upper-right servo to pin 9 
    RL.attach(5);   // Connect the signal wire of the lower-right servo to pin 10 
    LU.attach(6);   // Connect the signal wire of the upper-left  servo to pin 11 
    LL.attach(9);   // Connect the signal wire of the lower-left  servo to pin 12 
}

void Adjust()                            // Avoid the servo's fast spinning in initialization 
{                                        // RU,LU goes from array_cal[0] - 5 ,array_cal[2] + 5 degrees to array_cal[0],array_cal[2] degrees
    for(RU_Degree = array_cal[0] - 5; RU_Degree <= array_cal[0]; RU_Degree += 1) {
        RU.write(RU_Degree);             // in steps of 1 degree
        LU.write(LU_Degree--);           // tell servo to go to RU_Degreeition, LU_Degreeition in variable 'RU_Degree', 'LU_Degree'         
        delay(15);                       // waits 15ms for the servo to reach the RU_Degreeition
    }
}

void Ultrasonic()
{
  
  digitalWrite(Trig, LOW);   // Give the trigger pin low level 2μs
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // Give the trigger pin a high level of 10μs, here at least 10μs
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // Continue to low voltage to the trigger pin
  float Fdistance = pulseIn(Echo, HIGH);  // Read high time (unit: microsecond)
  Fdistance= Fdistance/58;       //Why divide by 58 equals centimeter, Y m = (X seconds * 344) / 2
  // X seconds = ( 2 * Y meters) / 344 = = "X seconds = 0.0058 * Y meters = = "cm = microseconds / 58
  Serial.print("Distance:");      //Output distance (unit: cm)
  Serial.println(Fdistance);        //Display distance
  Distance = Fdistance;
}

void Forward()
{for(int z=0; z<1; z++) {
    for(int x=0; x<num1; x++) {                    
        RU.slowmove (array_cal[0] + array_forward[x][0] , vel);    
        RL.slowmove (array_cal[1] + array_forward[x][1] , vel);
        LU.slowmove (array_cal[2] + array_forward[x][2] , vel);
        LL.slowmove (array_cal[3] + array_forward[x][3] , vel);
        delay(delay_Forward);
    }

}
}

void Backward()
{for(int z=0; z<3; z++) {
  for(int y=0; y<num2; y++) {                  
      RU.slowmove (array_cal[0] + array_back[y][0] , vel_Back);   
      RL.slowmove (array_cal[1] + array_back[y][1] , vel_Back);
      LU.slowmove (array_cal[2] + array_back[y][2] , vel_Back);
      LL.slowmove (array_cal[3] + array_back[y][3] , vel_Back);
      delay(delay_Back); 
                           }
                         }
}



void setup()  
{
   Serial.begin(9600);
    Servo_Init();
    RU.slowmove (array_cal[0] , vel);
    RL.slowmove (array_cal[1] , vel);
    LU.slowmove (array_cal[2] , vel);
    LL.slowmove (array_cal[3] , vel);
    delay(2000);
  pinMode(Echo, INPUT);    // Define ultrasonic input pin
  pinMode(Trig, OUTPUT);   // Define ultrasonic output pin
}

void loop() 
{ 
    Ultrasonic();
    if(Distance>20)
    {
      Forward();
    }else
    {Backward();
      }
    
}