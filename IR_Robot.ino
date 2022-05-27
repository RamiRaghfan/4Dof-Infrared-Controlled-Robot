
// uparrow      -- 804EC03F
// downarrow    -- 804E7A85
// leftarrow    -- 804E40BF
// rightarrow   -- 804E02FD
// MENU         -- 804E38C7
// EXIT         -- 804E18E7
// OK           -- 804EFA05

#include "IRremote.h"

#include <Servo.h>


const int AXIS1_PIN = 6;
const int AXIS2_PIN = 5;
const int AXIS3_PIN = 3;
const int GRIPPER_PIN = 9;


Servo AXIS1;  
Servo AXIS2;
Servo AXIS3; 
Servo GRIPPER;

int axis1_angle = 90;    // initial axis1_angle  for servo
int axis2_angle = 90;
int axis3_angle = 90;
int gripper_angle = 90;


int angleStep = 2;
int elbowStep = 25;
int baseStep = 3;
int gripperStep = 20;


boolean AXIS2_SHOULDER_UP = false;
boolean AXIS2_SHOULDER_DOWN = false;
boolean AXIS1_ELBOW_UP   = false;
boolean AXIS1_ELBOW_DOWN = false;
boolean AXIS3_BASE_LEFT = false;
boolean AXIS3_BASE_RIGHT = false;
boolean gripperClosing = false;
boolean gripperOpening = false;

const byte RECV_PIN = 7;   //IR receive pin
 
IRrecv irrecv(RECV_PIN);   //create instance of 'IRrecv'
decode_results results;    //create instance of 'decode_results'
 
unsigned long TimerTurning;
unsigned long TimerIncDec;
 
unsigned long   dummy;
unsigned long * TimerPtr = &dummy; //pointer to the current timer


void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); //start receive
  AXIS1.attach(AXIS1_PIN);
  AXIS2.attach(AXIS2_PIN);
  AXIS3.attach(AXIS3_PIN);
  GRIPPER.attach(GRIPPER_PIN);
} //                    E N D  O F  s e t u p ( )
 
 
 
//                            l o o p ( )
//**********************************************************************
void loop()
{
  if (irrecv.decode(&results)) //is there IR remote button code
  {
    Serial.println(results.value);
    processButton(); //process button press
    irrecv.resume(); //restart for next button press
  }
 
  //are we still within the adjustment time
  if (millis() - TimerTurning <= 300ul)
  {
      //is it time to increase/decrease the intensity
      if (millis() - TimerIncDec >= 200ul)
      {
        TimerIncDec = millis();
   
        if (AXIS1_ELBOW_UP == true) //Increase
        {
          if (axis1_angle >= 0 && axis1_angle <= 180)
          {
            axis1_angle = axis1_angle + elbowStep;
            if (axis1_angle > 180)
            {
              axis1_angle = 180;
            }

            AXIS1.write(axis1_angle); // move the servo to desired axis1_angle
            // Serial.print("Moved to: ");
            // Serial.print(axis1_angle);  // print the axis1_angle
            // Serial.println(" degree");

          }
        }


        else if (AXIS1_ELBOW_DOWN == true) //Decrease
        {
          if (axis1_angle > 0 && axis1_angle <= 180)
          {
            axis1_angle = axis1_angle - elbowStep;
            if (axis1_angle < 0)
            {
              axis1_angle = 0;
            }
          
            AXIS1.write(axis1_angle); // move the servo to desired axis1_angle
            // Serial.print("Moved to: ");
            // Serial.print(axis1_angle);  // print the axis1_angle
            // Serial.println(" degree");
            
          }
        }

      else if(AXIS2_SHOULDER_UP == true)
      {

        if (axis2_angle >= 0 && axis2_angle <= 180)
        {
          axis2_angle = axis2_angle + angleStep;
          if (axis2_angle > 180)
          {
            axis2_angle = 180;
          }


         AXIS2.write(axis2_angle); // move the servo to desired axis2_angle
         // Serial.print("SHOULDER Moved to: ");
         // Serial.print(axis2_angle);  // print the axis2_angle
         // Serial.println(" degree");

          
        }
      }


        else if(AXIS2_SHOULDER_DOWN == true)
        {

          if (axis2_angle > 0 && axis2_angle <= 180)
          {
            axis2_angle = axis2_angle - angleStep;
            if (axis2_angle < 0)
            {
              axis2_angle = 0;
            }

            AXIS2.write(axis2_angle); // move the servo to desired axis2_angle
            // Serial.print("Moved to: ");
            // Serial.print(axis2_angle);  // print the axis2_angle
            // Serial.println(" degree");

          }

        } 


      else if (AXIS3_BASE_RIGHT == true) 
      {

        if (axis3_angle >= 0 && axis3_angle <= 180) 
        {
          axis3_angle = axis3_angle + baseStep;
          if (axis3_angle > 130) {
            axis3_angle = 140;
          }
          
          AXIS3.write(axis3_angle); // move the servo to desired axis3_angle
          // Serial.print("SHOULDER Moved to: ");
          // Serial.print(axis3_angle); // print the axis3_angle
          // Serial.println(" degree");

        }
      } 
      
      else if (AXIS3_BASE_LEFT == true) 
      {

        if (axis3_angle > 0 && axis3_angle <= 180)
        {
          axis3_angle = axis3_angle - baseStep;
        if(axis3_angle < 60)
          {
            axis3_angle = 40;
          }

          AXIS3.write(axis3_angle); // move the servo to desired axis3_angle
          // Serial.print("Moved to: ");
          // Serial.print(axis3_angle); // print the axis3_angle
          // Serial.println(" degree");

        }

      }


      else if (gripperOpening == true) 
      {

        if (gripper_angle >= 0 && gripper_angle <= 180) 
        {
          gripper_angle = gripper_angle + gripperStep;
          if (gripper_angle > 130) {
            gripper_angle = 130;
          }
          
          GRIPPER.write(gripper_angle); // move the servo to desired gripper_angle
          // Serial.print("gripper");
          // Serial.print(gripper_angle); // print the gripper_angle
          // Serial.println(" degree");

        }
      } 
      
      else if (gripperClosing == true) 
      {

        if (gripper_angle > 0 && gripper_angle <= 180)
        {
          gripper_angle = gripper_angle - gripperStep;
        if(gripper_angle < 75)
          {
            gripper_angle = 75;
          }

          GRIPPER.write(gripper_angle); // move the servo to desired axis3_angle
          // Serial.print("gripper");
          // Serial.print(gripper_angle); // print the axis3_angle
          // Serial.println(" degree");

        }

      }

      }
  }
  else
  {
    AXIS1_ELBOW_UP = false;
    AXIS1_ELBOW_DOWN = false;
    AXIS2_SHOULDER_UP = false;
    AXIS2_SHOULDER_DOWN = false;
    AXIS3_BASE_LEFT = false;
    AXIS3_BASE_RIGHT = false;
    gripperOpening = false;
    gripperClosing = false;
  }
  
} //                   E N D  O F  l o o p ( )
 
 
 
//======================================================================
//                       F U N C T I O N S
//======================================================================
 
//                   p r o c e s s B u t t o n ( )
//**********************************************************************
//process IR remote button presses
void processButton()
{
  switch (results.value)
  { 
    case 0x804EC03F:                                           
      {
        // Serial.println("UP_SHOULDER");
        // Serial.println("^^");
        TimerPtr = &TimerTurning;  //point to this timer
        AXIS2_SHOULDER_UP = true;       
        AXIS2_SHOULDER_DOWN = false;
        AXIS1_ELBOW_DOWN = false;
        AXIS1_ELBOW_UP = false;
        AXIS3_BASE_LEFT = false;
        AXIS3_BASE_RIGHT = false;
        TimerTurning = millis();
        TimerIncDec = millis();
      }
      break;
 
    //**********************
    case 0x804E7A85:                                           
      {  
        // Serial.println("DOWN_SHOULDER");
        // Serial.println("VV");
        TimerPtr = &TimerTurning;  //point to this timer
        AXIS2_SHOULDER_DOWN = true;       //enable intensity up adjustment
        AXIS2_SHOULDER_UP = false;
        AXIS1_ELBOW_DOWN = false;
        AXIS1_ELBOW_UP = false;
        AXIS3_BASE_LEFT = false;
        AXIS3_BASE_RIGHT = false;
        TimerTurning = millis();
        TimerIncDec = millis();   
      }
      break;
 
    //**********************
    case 0x804E38C7:                                           
      { 
        // Serial.println("UP_ELBOW");
        TimerPtr = &TimerTurning;  //point to this timer
        AXIS1_ELBOW_UP = true;       
        AXIS1_ELBOW_DOWN = false;
        AXIS2_SHOULDER_UP = false;
        AXIS2_SHOULDER_DOWN = false;
        AXIS3_BASE_LEFT = false;
        AXIS3_BASE_RIGHT = false;
        gripperOpening = false;
        gripperClosing = false;
        TimerTurning = millis();
        TimerIncDec = millis();
      }
      break;
 
    //**********************
   case 0x804E18E7:                                           
      {
        // Serial.println("DOWN_ELBOW");
        TimerPtr = &TimerTurning;  //point to this timer
        AXIS1_ELBOW_DOWN = true;     
        AXIS1_ELBOW_UP = false;
        AXIS2_SHOULDER_DOWN = false;
        AXIS2_SHOULDER_UP = false;
        AXIS3_BASE_LEFT = false;
        AXIS3_BASE_RIGHT = false;
        gripperOpening = false;
        gripperClosing = false;        
        TimerTurning = millis();
        TimerIncDec = millis();
      }
      break;

      case 0x804E02FD:                                           
      { 
        // Serial.println("LEFT BASE");
        TimerPtr = &TimerTurning;  //point to this timer
        AXIS3_BASE_LEFT = true;
        AXIS1_ELBOW_UP = false;       
        AXIS1_ELBOW_DOWN = false;
        AXIS2_SHOULDER_UP = false;
        AXIS2_SHOULDER_DOWN = false;
        gripperOpening = false;
        gripperClosing = false;
        TimerTurning = millis();
        TimerIncDec = millis();
      }
      break;
 
    //**********************
   case 0x804E40BF:                                           
      {
        // Serial.println("RIGHT BASE");
        TimerPtr = &TimerTurning;  //point to this timer
        AXIS3_BASE_RIGHT = true;
        AXIS1_ELBOW_DOWN = false;     
        AXIS1_ELBOW_UP = false;
        AXIS2_SHOULDER_DOWN = false;
        AXIS2_SHOULDER_UP = false;
        gripperOpening = false; 
        gripperClosing = false;
        TimerTurning = millis();
        TimerIncDec = millis();
      }
      break;

/*up2 -- 804EE01F
down2 -- 804E42BD
*/
      case 0x804EE01F:
      {
        // Serial.println("GRIPPER CLOSE");
        TimerPtr = &TimerTurning;  //point to this timer
        gripperClosing = true;
        gripperOpening = false;
        AXIS3_BASE_RIGHT = false;
        AXIS1_ELBOW_DOWN = false;     //enable intensity down adjustment
        AXIS1_ELBOW_UP = false;
        AXIS2_SHOULDER_DOWN = false;
        AXIS2_SHOULDER_UP = false;
        TimerTurning = millis();
        TimerIncDec = millis();

      }
      break;

      case 0x804E42BD:                                           
      { 
        // Serial.println("GRIPPER OPEN");
        TimerPtr = &TimerTurning;  //point to this timer
        gripperOpening = true;
        gripperClosing = false;
        AXIS3_BASE_LEFT = false;
        AXIS1_ELBOW_UP = false;       
        AXIS1_ELBOW_DOWN = false;
        AXIS2_SHOULDER_UP = false;
        AXIS2_SHOULDER_DOWN = false;
        TimerTurning = millis();
        TimerIncDec = millis();
      }
      break;

 
    case 0xFFFFFFFF: //Repeat code
      {
        // Serial.println("REPEAT");
        *TimerPtr = millis();       //reset the current timer
      }
      break;
 
  } // END switch case
 
} //             E N D  o f  p r o c e s s B u t t o n ( )
 
//**********************************************************************
 
//======================================================================
//                        E N D  O F  C O D E
//======================================================================6
