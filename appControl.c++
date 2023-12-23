#include "VarSpeedServo.h"  //include the VarSpeedServo library
//#include <Servo.h>

VarSpeedServo RU;  //Right Upper
VarSpeedServo RL;  //Right Lower
VarSpeedServo LU;  //Left Upper
VarSpeedServo LL;  //Left Lower


//String val="";
int incomingByte = 0;          // Received data byte
String inputString = "";         // Used to store received content
boolean newLineReceived = false; // Previous data end mark
boolean startBit  = false;  //Agreement start sign
int num_reveice=0;



//vel(min), delay_Forward(max) = (5, 2000) 
const int vel = 40, vel_Back = 40;//15,vel_Right= 30,vel_Left= 30;                   //vel(mid), delay_Forward(mid) = (20, 750) 
const int delay_Forward = 300, delay_Back = 450; //750    //vel(max), delay_Forward(min)= (256, 50)
const int delay_Right = 200, delay_Left = 200;                                                     //wonderful ---> (10, 700) (50, 500) (100, 100) (100, 300) (100, 500)

int vel_Dance1 = 30,    vel_Dance2 = 25,    vel_Dance3 = 40;     
int delay_Dance1 = 300, delay_Dance2 = 750, delay_Dance3 = 200;  

int vel_Dance4 = 40,    vel_Dance5 = 40,    vel_Dance6 = 30;
int delay_Dance4 = 400, delay_Dance5 = 400, delay_Dance6 = 500;

const int array_cal[4] = {1,80,90,92};  
//const int array_cal[4] = {77,82,95,90};
 
int RU_Degree = 0, LU_Degree = array_cal[2] + 5;

const int num_dance1 = 10;
const int array_dance1[num_dance1][4] =
{ 
//slide to the left 0-4
    {0,-20,0,0},  
    {0,-40,0,20},
    {0,-20,0,40},
    {0,0,0,20},
    {0,0,0,0},
    
//slide to the right 5-9
    {0,0,0,20},  
    {0,-20,0,40},
    {0,-40,0,20},
    {0,-20,0,0},
    {0,0,0,0}, 
};

const int num_dance2 = 32;
const int array_dance2[num_dance2][4] =
{ 
//left foot support 0-15
    {20,0,40,0},
    {20,-30,40,-30}, 
    {20,-30,10,-30},
    {20,-30,40,-30}, 
    {20,-30,10,-30},

    {20,-30,40,-30}, 
    {20,0,40,-30},
    {20,80,40,-30},
    {20,0,40,-30},
    {20,-80,40,-30},        
    {20,0,40,-30},
    {20,80,40,-30},
    {20,0,40,-30},
    {20,-30,40,-30},    
    {20,0,40,0},
    {0,0,0,0}, 
     
//right foot support 16-31
    {-40,0,-20,0},
    {-40,40,-20,30}, 
    {-20,40,-20,30}, 
    {-40,40,-20,30}, 
    {-20,40,-20,30}, 

    {-40,40,-20,30}, 
    {-40,40,-20,0},
    {-40,40,-20,-80},
    {-40,40,-20,0},
    {-40,40,-20,80},        
    {-40,40,-20,0},
    {-40,40,-20,-80},
    {-40,40,-20,0},
    {-40,40,-20,30},    
    {-40,0,-20,0},
    {0,0,0,0},
};

const int num_dance3 = 8;        //Small broken
const int array_dance3[num_dance3][4] =
{ 
    {0,-40,0,0},
    {20,-30,20,20},
    {40,0,40,30},   
    {0,0,0,40},
    {-20,-20,-20,30},
    {-40,-30,-40,0},

    {0,-40,0,0},
    {0,0,0,0},
};

const int num_dance4 = 20;      //In-situ ups and downs, increasing in angle
const int array_dance4[num_dance4][4] =
{     
    {0,-20,0,20},   
    {0,0,0,0},
    {0,-20,0,20},
    {0,0,0,0},
    {0,-20,0,20},
    {0,0,0,0},
    {0,-20,0,20},
    {0,0,0,0},
    
    {0,-50,0,50},
    {0,0,0,0},    
    {0,-50,0,50},
    {0,0,0,0},    
    {0,-50,0,50},
    {0,0,0,0},    
    {0,-50,0,50},
    {0,0,0,0},
    
    {0,-40,0,40},
    {0,-50,0,50},
    {0,-60,0,60},
    {0,0,0,0,},
};

const int num_hold_up = 20;      
const int array_hold_up[num_hold_up][4] =
{     
    {0,20,0,-20},   
    {0,0,0,0},
    {0,20,0,-20},
    {0,0,0,0},
    {0,20,0,-20},
    {0,0,0,0},
    {0,20,0,-20},
    {0,0,0,0},
    
    {0,50,0,-50},
    {0,0,0,0},    
    {0,50,0,-50},
    {0,0,0,0},    
    {0,50,0,-50},
    {0,0,0,0},    
    {0,50,0,-50},
    {0,0,0,0},
    
    {0,40,0,-40},
    {0,50,0,-50},
    {0,60,0,-60},
    {0,0,0,0,},
};








const int num_dance5 = 17;
const int array_dance5[num_dance5][4] =
{ 
    {35,0,15,0},    
    {35,30,15,30},   
    {-35,30,15,30},   
    {-20,0,15,0},
    {0,0,0,0},

    {0,-40,0,40},    //Inner flip foot
    {-30,-40,-20,40},
    {0,-40,0,40},
    {20,-40,30,40},    

    
    {0,-40,0,40},    //In place to rise and fall
    {20,-40,-20,40},   
    {20,-20,-20,20},
    {20,0,-20,0},   
    {-20,-10,20,10},
    {-10,-30,10,30},

    {0,-40,0,40},
    {0,0,0,0},
};

const int num_dance6 = 32;      
const int array_dance6[num_dance6][4] =
{   
    {0,-40,0,-20},        //Outer Eight Steps - Advance
    {25,-40,18,-20},
    {25,0,18,0},
    {0,20,0,40},
    {-18,20,-25,40},
    {-18,0,-25,0},
      
    {0,-40,0,-20},        //Outer Eight Steps - Stepping In Place
    {25,-40,18,-20},
    {0,0,0,0},
    {0,20,0,40},
    {-18,20,-25,40},
    {0,0,0,0},

    {0,-40,0,-20},        //Outer Eight Steps - Backward
    {-25,-40,-18,-20},
    {-25,0,-18,0},
    {0,20,0,40},
    {18,20,25,40},
    {18,0,25,0},

    {0,-40,0,-20},        //Small step - forward
    {30,-40,30,-20},
    {30,0,30,0},
    {0,20,0,40},
    {-30,20,-30,40},
    {-30,0,-30,0},
  
    {0,-40,0,-20},        //Small step - back
    {-30,-40,-30,-20},
    {-30,0,-30,0},
    {0,20,0,40},
    {30,20,30,40},
    {30,0,30,0},

    {15,0,15,0},
    {0,0,0,0},
};

const int num1 = 8;
const int array_forward[num1][4] =  
{
    {0,-40,0,-20},        //Pace - advance
    {30,-40,30,-20},
    {30,0,30,0},
    {0,20,0,40},
    {-30,20,-30,40},
    {-30,0,-30,0},
    {-15,0,-15,0},
    {0,0,0,0},
};

const int num2 = 8; 
const int array_turn[num2][4] =  
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


const int num3 = 10; 
const int array_turnright[num3][4] =  
{      //Turn right
//    {0,1,0,15},
//    {0,10,0,35},
//    {0,15,0,50},
//    {-30,15,0,50},
//    {-30,5,0,20},      
//    {-30,0,0,0},   
//    {-15,0,0,0},
//    {0,0,0,0},
  

    {0,10,0,15},
    {0,10,0,35},
    {0,15,0,60},
    {-30,20,0,60},
    {-30,5,0,20},
    {-30,0,0,0},      
    {-25,0,0,0},   
    {-15,0,0,0},
    {0,0,0,0},
};



const int num4 = 10; 
const int array_turnleft[num4][4] =  
{     
  //Turn left
//    {0,-15,0,-1},
//    {0,-35,0,-10},
//    {0,-50,0,-15},
//    {0,-50,30,-15},
//    {0,-20,30,-5},      
//    {0,0,30,0},
//    {0,0,25,0},   
//    {0,0,15,0},
//    {0,0,0,0},

    {0,-15,0,-10},
    {0,-35,0,-10},
    {0,-60,0,-15},
    {0,-60,30,-20},
    {0,-20,30,-5},      
    {0,0,30,0},
    {0,0,25,0},   
    {0,0,15,0},
    {0,0,0,0},


};
//#define INSTALL
//#define CALIBRATION
#define RUN

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



void Slide_2_Left(int times)
{
    for(int time1 = 0; time1 < times; time1++) { 
        for(int z=0; z<5; z++) {                     
            RU.slowmove (array_cal[0] + array_dance1[z][0] , vel_Dance1);   
            RL.slowmove (array_cal[1] + array_dance1[z][1] , vel_Dance1);
            LU.slowmove (array_cal[2] + array_dance1[z][2] , vel_Dance1);
            LL.slowmove (array_cal[3] + array_dance1[z][3] , vel_Dance1);
            delay(delay_Dance1); 
        } 
    }
}

void Slide_2_Right(int times)
{
    for(int time1 = 0; time1 < times; time1++) {
        for(int z=5; z<10; z++) {                     
            RU.slowmove (array_cal[0] + array_dance1[z][0] , vel_Dance1);   
            RL.slowmove (array_cal[1] + array_dance1[z][1] , vel_Dance1);
            LU.slowmove (array_cal[2] + array_dance1[z][2] , vel_Dance1);
            LL.slowmove (array_cal[3] + array_dance1[z][3] , vel_Dance1);
            delay(delay_Dance1); 
        }   
    }
}

void Left_Foot_Support()
{
    for(int z=0; z<16; z++) { //z<12
        if ( z > 5 && z < 14) {   //z(1,10)
            vel_Dance2 = 50;
            delay_Dance2 = 200;
        }
        else { 
        vel_Dance2 = 25; 
        delay_Dance2 = 750;
        }
                    
        RU.slowmove (array_cal[0] + array_dance2[z][0] , vel_Dance2);   
        RL.slowmove (array_cal[1] + array_dance2[z][1] , vel_Dance2);
        LU.slowmove (array_cal[2] + array_dance2[z][2] , vel_Dance2);
        LL.slowmove (array_cal[3] + array_dance2[z][3] , vel_Dance2);
        delay(delay_Dance2); 
    }
}

void Right_Foot_Support()
{
    for(int z=16; z<32; z++) { //z<24
        if ( z > 21 && z < 30) {   //z(13,22)
            vel_Dance2 = 50;
            delay_Dance2 = 200;
        }
        else { 
        vel_Dance2 = 25; 
        delay_Dance2 = 750;
        }
                    
        RU.slowmove (array_cal[0] + array_dance2[z][0] , vel_Dance2);   
        RL.slowmove (array_cal[1] + array_dance2[z][1] , vel_Dance2);
        LU.slowmove (array_cal[2] + array_dance2[z][2] , vel_Dance2);
        LL.slowmove (array_cal[3] + array_dance2[z][3] , vel_Dance2);
        delay(delay_Dance2); 
    }
}

void Dancing1_2()
{
    Slide_2_Left(2);
    Left_Foot_Support();
    
    Slide_2_Right(2);
    Right_Foot_Support();
}

void Dancing3(int Times = 1, int Vel = 40, int Delay = 250, int low = 0, int high = 0)
{   
    for(int time3 = 0; time3 < Times; time3++) {
        for(int z=0; z<6; z++) {
            if ( time3 > 1 && time3 < 4) {
            vel_Dance3 = Vel;
            delay_Dance3 = Delay;
            }
            else { 
            vel_Dance3 = 40; 
            delay_Dance3 = 200;
            }                     
            
            RU.slowmove (array_cal[0] + array_dance3[z][0] , vel_Dance3);   
            RL.slowmove (array_cal[1] + array_dance3[z][1] , vel_Dance3);
            LU.slowmove (array_cal[2] + array_dance3[z][2] , vel_Dance3);
            LL.slowmove (array_cal[3] + array_dance3[z][3] , vel_Dance3);
            delay(delay_Dance3); 
        } 
    }
    for(int z=6; z<8; z++) {                     
            RU.slowmove (array_cal[0] + array_dance3[z][0] , vel_Dance3);   
            RL.slowmove (array_cal[1] + array_dance3[z][1] , vel_Dance3);
            LU.slowmove (array_cal[2] + array_dance3[z][2] , vel_Dance3);
            LL.slowmove (array_cal[3] + array_dance3[z][3] , vel_Dance3);
            delay(delay_Dance3); 
        }       
}


void hold_up()
{    int vel_hold_up = 10;
     int delay_hold_up= 1500;
  for(int z=16; z<20; z++) 
  {
        RU.slowmove (array_cal[0] + array_hold_up[z][0] , vel_hold_up);   
        RL.slowmove (array_cal[1] + array_hold_up[z][1] , vel_hold_up);
        LU.slowmove (array_cal[2] + array_hold_up[z][2] , vel_hold_up);
        LL.slowmove (array_cal[3] + array_hold_up[z][3] , vel_hold_up);
        delay(delay_hold_up); 
    } 
  
}


void large_hold_up()
{  int vel_hold_up = 40;
   int delay_hold_up = 200;
  for(int x = 0; x < 4; x++) {
  for(int z=6; z<16; z++) 
  {
        RU.slowmove (array_cal[0] + array_hold_up[z][0] , vel_hold_up);   
        RL.slowmove (array_cal[1] + array_hold_up[z][1] , vel_hold_up);
        LU.slowmove (array_cal[2] + array_hold_up[z][2] , vel_hold_up);
        LL.slowmove (array_cal[3] + array_hold_up[z][3] , vel_hold_up);
        delay(delay_hold_up); 
    } 
  }
}


void large_Shrink()
{ vel_Dance4 = 40;
  delay_Dance4 = 200;
  for(int x = 0; x < 4; x++) {
  for(int z=6; z<16; z++) 
  {
        RU.slowmove (array_cal[0] + array_dance4[z][0] , vel_Dance4);   
        RL.slowmove (array_cal[1] + array_dance4[z][1] , vel_Dance4);
        LU.slowmove (array_cal[2] + array_dance4[z][2] , vel_Dance4);
        LL.slowmove (array_cal[3] + array_dance4[z][3] , vel_Dance4);
        delay(delay_Dance4); 
    } 
  }
}

void Shrink()
{ vel_Dance4 = 10;
  delay_Dance4 = 1500;
  
  for(int z=16; z<20; z++) 
  {
        RU.slowmove (array_cal[0] + array_dance4[z][0] , vel_Dance4);   
        RL.slowmove (array_cal[1] + array_dance4[z][1] , vel_Dance4);
        LU.slowmove (array_cal[2] + array_dance4[z][2] , vel_Dance4);
        LL.slowmove (array_cal[3] + array_dance4[z][3] , vel_Dance4);
        delay(delay_Dance4); 
     
  }
}


void small_Shrink()
{ vel_Dance4 = 10;
  delay_Dance4 = 1500;
  for(int z=8; z<16; z++) 
  {
        RU.slowmove (array_cal[0] + array_dance4[z][0] , vel_Dance4);   
        RL.slowmove (array_cal[1] + array_dance4[z][1] , vel_Dance4);
        LU.slowmove (array_cal[2] + array_dance4[z][2] , vel_Dance4);
        LL.slowmove (array_cal[3] + array_dance4[z][3] , vel_Dance4);
        delay(delay_Dance4); 
    } 
  
}

void Dancing4()
{  
    for(int z=0; z<num_dance4; z++) {
        if ( z > 17) {
            vel_Dance4 = 10;
            delay_Dance4 = 1500;
            }
        else {
            vel_Dance4 = 40;
            delay_Dance4 = 400;
            }
                 
        RU.slowmove (array_cal[0] + array_dance4[z][0] , vel_Dance4);   
        RL.slowmove (array_cal[1] + array_dance4[z][1] , vel_Dance4);
        LU.slowmove (array_cal[2] + array_dance4[z][2] , vel_Dance4);
        LL.slowmove (array_cal[3] + array_dance4[z][3] , vel_Dance4);
        delay(delay_Dance4); 
    } 
}




void Turn_inside()
{    for(int x = 0; x < 2; x++) {
        for(int z=5; z<9; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , 30);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , 30);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , 30);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , 30);
            delay(550); 
        } 
    }
      for(int z=15; z<17; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , 30);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , 30);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , 30);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , 30);
            delay(550); 
        } 
    
  }


void In_place()
{   for(int x = 0; x < 3; x++) {
        for(int z=9; z<15; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , vel_Dance5);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , vel_Dance5);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , vel_Dance5);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , vel_Dance5);
            delay(300); 
        } 
    }

     for(int z=15; z<17; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , 30);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , 30);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , 30);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , 30);
            delay(550); 
        } 
  }





void Dancing5()
{   
        for(int z=0; z<5; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , vel_Dance5);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , vel_Dance5);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , vel_Dance5);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , vel_Dance5);
            delay(delay_Dance5); 
        
    }
   
    for(int x = 0; x < 2; x++) {
        for(int z=5; z<9; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , 30);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , 30);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , 30);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , 30);
            delay(550); 
        } 
    }
    
    for(int x = 0; x < 3; x++) {
        for(int z=9; z<15; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , vel_Dance5);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , vel_Dance5);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , vel_Dance5);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , vel_Dance5);
            delay(300); 
        } 
    }    
    for(int z=15; z<17; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , 10);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , 10);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , 10);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , 10);
            delay(1500); 
        }   
}





void Walking_in_place()
{ for(int x = 0; x < 3; x++) {
        for(int z=6; z<12; z++) {                     
            RU.slowmove (array_cal[0] + array_dance6[z][0] , 40);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , 40);
            LU.slowmove (array_cal[2] + array_dance6[z][2] , 40);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , 40);
            delay(400); 
        } 
  }

}
  
void Dancing6()
{   
    const int array_cal_0 = array_cal[0] + 10 , array_cal_2 = array_cal[2] - 10;
    
    for(int x = 0; x < 3; x++) {
        for(int z=0; z<6; z++) {                     
            RU.slowmove (array_cal_0 + array_dance6[z][0] , vel_Dance6);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , vel_Dance6);
            LU.slowmove (array_cal_2 + array_dance6[z][2] , vel_Dance6);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , vel_Dance6);
            delay(delay_Dance6); 
        } 
    }
   
    for(int x = 0; x < 3; x++) {
        for(int z=6; z<12; z++) {                     
            RU.slowmove (array_cal_0 + array_dance6[z][0] , 40);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , 40);
            LU.slowmove (array_cal_2 + array_dance6[z][2] , 40);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , 40);
            delay(400); 
        } 
    }
    
    for(int x = 0; x < 3; x++) {
        for(int z=12; z<18; z++) {                     
            RU.slowmove (array_cal_0 + array_dance6[z][0] , vel_Dance6);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , vel_Dance6);
            LU.slowmove (array_cal_2 + array_dance6[z][2] , vel_Dance6);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , vel_Dance6);
            delay(delay_Dance6); 
        } 
    }  
    for(int x = 0; x < 3; x++) {
        for(int z=18; z<24; z++) {                     
            RU.slowmove (array_cal[0] + array_dance6[z][0] , vel_Dance6);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , vel_Dance6);
            LU.slowmove (array_cal[2] + array_dance6[z][2] , vel_Dance6);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , vel_Dance6);
            delay(delay_Dance6); 
        } 
    }

    for(int x = 0; x < 3; x++) {
        for(int z=24; z<30; z++) {                     
            RU.slowmove (array_cal[0] + array_dance6[z][0] , vel_Dance6);   
            RL.slowmove (array_cal[1] + array_dance6[z][1] , vel_Dance6);
            LU.slowmove (array_cal[2] + array_dance6[z][2] , vel_Dance6);
            LL.slowmove (array_cal[3] + array_dance6[z][3] , vel_Dance6);
            delay(delay_Dance6); 
        } 
    }
    for(int z=30; z<32; z++) {                     
            RU.slowmove (array_cal[0] + array_dance5[z][0] , 10);   
            RL.slowmove (array_cal[1] + array_dance5[z][1] , 10);
            LU.slowmove (array_cal[2] + array_dance5[z][2] , 10);
            LL.slowmove (array_cal[3] + array_dance5[z][3] , 10);
            delay(1500); 
        }     
}

void Forward()
{
    for(int x=0; x<num1; x++) {                    
        RU.slowmove (array_cal[0] + array_forward[x][0] , vel);    
        RL.slowmove (array_cal[1] + array_forward[x][1] , vel);
        LU.slowmove (array_cal[2] + array_forward[x][2] , vel);
        LL.slowmove (array_cal[3] + array_forward[x][3] , vel);
        delay(delay_Forward);
    }
}

void Backward()
{   
        for(int y=0; y<num2; y++) {                  
            RU.slowmove (array_cal[0] + array_turn[y][0] , vel_Back);   
            RL.slowmove (array_cal[1] + array_turn[y][1] , vel_Back);
            LU.slowmove (array_cal[2] + array_turn[y][2] , vel_Back);
            LL.slowmove (array_cal[3] + array_turn[y][3] , vel_Back);
            delay(delay_Back); 
        }
    
}
void turn_left()
{
  for(int x=0; x<5; x++)
  {
    for(int z=0; z<num4; z++)
       {                     
            RU.slowmove (array_cal[0] + array_turnleft[z][0] , vel);   
            RL.slowmove (array_cal[1] + array_turnleft[z][1] , vel);
            LU.slowmove (array_cal[2] + array_turnleft[z][2] , vel);
            LL.slowmove (array_cal[3] + array_turnleft[z][3] , vel);
            delay(delay_Left); 
        }
  }      
}   


void turn_right()
{
  for(int x=0; x<5; x++)
  {
    for(int z=0; z<num3; z++)
       {                     
            RU.slowmove (array_cal[0] + array_turnright[z][0] ,vel);   
            RL.slowmove (array_cal[1] + array_turnright[z][1] ,vel);
            LU.slowmove (array_cal[2] + array_turnright[z][2] ,vel);
            LL.slowmove (array_cal[3] + array_turnright[z][3] ,vel);
            delay(delay_Right); 
        }
  }      
}   

void setup()  
{
    Serial.begin(9600); //  set the baud rate to 9600
#ifdef INSTALL
    Servo_Init();
  
    RU.slowmove (90 , vel);
    RL.slowmove (90 , vel);
    LU.slowmove (90 , vel);
    LL.slowmove (90 , vel);
    while(1);
#endif

#ifdef CALIBRATION 
    Servo_Init();  
    Adjust();
    
    RL.slowmove (array_cal[1] , vel);
    LL.slowmove (array_cal[3] , vel);
    delay(2000);
    while(1);
#endif

#ifdef RUN 
    Servo_Init();
    Adjust(); 
       
    RL.slowmove (array_cal[1] , vel);
    LL.slowmove (array_cal[3] , vel);
    delay(2000);
#endif
}

void loop() 
{   
//    Dancing1_2();
//    delay(500);    
//    Dancing3(5,20,400);
//    delay(500);    
//    Dancing4();
//    delay(500);    
//    Dancing5();
//    delay(500);    
//    Dancing6();
//    delay(500); 
//
// while (Serial.available() > 0)  
//    {
//        val+= char(Serial.read());
//        delay(2);
//    }

//    if(Serial.available())   // if receive the data
//  {
//    val=Serial.read();    // read the received data
//    Serial.println(val);
//   

while (Serial.available())
  {
    incomingByte = Serial.read();              //One byte is read one byte, and the next sentence is read into the string array to form a completed packet.
    if (incomingByte == '%')
    {
      num_reveice = 0;
      startBit = true;
    }
    if (startBit == true)
    {
      num_reveice++;
      inputString += (char) incomingByte;     // Full-duplex serial port can be added without delay, half-duplex is added
    }
    if (startBit == true && incomingByte == '#')
    {
      newLineReceived = true;
      startBit = false;
    }
    
    if(num_reveice >= 20)
    {
      num_reveice = 0;
      startBit = false;
      newLineReceived = false;
      inputString = "";
    }  
  }



if(newLineReceived)
{
    switch(inputString[1])   
    { case 'A':  hold_up();;  break;
      case 'B':  Shrink();  break;
      case 'C':  Slide_2_Right(3);  break;
      case 'D':  In_place();  break;
      case 'E':  Turn_inside();  break;   // execute the corresponding function when receive the value 
      case 'F':  Dancing3(5,20,400);  break;//
      case 'G':  Left_Foot_Support();  break;
      case 'H':  Right_Foot_Support();  break;
      case '4':  Forward();;  break;
      case '5':  turn_left();  break;
      case '6':  turn_right();  break;
      case '7':  Backward();  break;
      default:break;
    }

      inputString = "";   // clear the string
      newLineReceived = false;
}   

}