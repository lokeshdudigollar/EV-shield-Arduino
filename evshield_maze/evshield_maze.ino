/*
 * Move unlimited forward
 * wait till front distance is less than 15cm
 * if path on front is blocked at less than 15cm
 * wait for 20seconds
 * turn ultra to right, wait for 10 seconds, measure the right path, wait for 10 seconds
 * turn ultra to left wait for 10 seconds, measure the left path, wait for 10 seconds
 * compare the left and right distnace 
 * turn ultra on front
 * if right is more move the left wheel
 * if left is more move the right wheel
 * repeat from step 1
 */
/*Left hand algorithm
 * Turn left if you can
 * Move straight if you can 
 * Trun right if you can
 * 1)Store all paths taken at every intersection in an array with  left as 'L' Right as 'R' Sraight as 'S' and Uturn as 'B' 
 * 2)After completing the path remove all B and find shortest path.
 * 3)When kept from srart point follow the shortest path
 * 
 * LBR =B/LBS=R/RBL=B/SBL=R/SBS=B/LBL=S
 */






#include <Wire.h>
#include <EVShield.h>
#include <EVShieldAGS.h>
#include <EVs_EV3Ultrasonic.h>

// setup for this example:
// attach external power to EVShield.
// attach 2 motors to motor ports bank A
// attach ultrasonic sensor to BAS1

EVShield          evshield(0x34,0x36);
EVs_EV3Ultrasonic myUS;
long            rotations = 2;  // Define variable rotations and set
int front, right,left;
long degree=100;

  
void
setup()
{
  //initialize hardware
    evshield.init( SH_HardwareI2C );

  //  initialize the sensor
    myUS.init( &evshield, SH_BAS1 );
    myUS.setMode(MODE_Sonar_CM);

  // Wait until user presses GO button to continue the program
    while (!evshield.getButtonState(BTN_GO)) {
        if (millis() % 2000 < 3) {
            Serial.println("Press GO button to continue");
        }
    }


    // reset motors.

    evshield.bank_a.motorReset();
    evshield.bank_b.motorReset();

 
}


//int count = 0;
//int dir;
void 
loop()
{

  //Measure the right distance
  right = myUS.getDist();
  delay(200);
  //Turn medium motor to front
  evshield.bank_b.motorRunDegrees(SH_Motor_1, 
                     SH_Direction_Forward,
                     SH_Speed_Medium, 
                     degree, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
  //Measure front distance
  front = myUS.getDist();
  delay(200);
  //Turn left
  evshield.bank_b.motorRunDegrees(SH_Motor_1, 
                     SH_Direction_Forward,
                     SH_Speed_Medium, 
                     degree, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);

  //Measure the left distance
  left = myUS.getDist(); 
  delay(200);

  

  //Measure the left distance
  //left = myUS.getDist();
  //delay(200);
  //Turn medium motor to front
  evshield.bank_b.motorRunDegrees(SH_Motor_1, 
                     SH_Direction_Reverse,
                     SH_Speed_Medium, 
                     degree, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
  //Measure front distance
  front = myUS.getDist();
  delay(200);
  //Turn right
  evshield.bank_b.motorRunDegrees(SH_Motor_1, 
                     SH_Direction_Reverse,
                     SH_Speed_Medium, 
                     degree, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);

  //Measure the left distance
  right = myUS.getDist(); 
  delay(200);
  
  

  if (front>20 && right<20 && left <20){
        //move forward
        evshield.bank_a.motorRunUnlimited(SH_Motor_Both, 
                                          SH_Direction_Reverse,SH_Speed_Medium);
        
    }

  else if (right>20){
    //turn right
    evshield.bank_a.motorRunRotations(SH_Motor_2, 
                     SH_Direction_Reverse,
                     SH_Speed_Medium, 
                     rotations, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
    }

  else if (left >20){
    if (right<20){
      //turn left
      evshield.bank_a.motorRunRotations(SH_Motor_1, 
                     SH_Direction_Reverse,
                     SH_Speed_Medium, 
                     rotations, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
    }
    }
    
    

  else if (front>20 && right>20 && left >20){
    //stop
    evshield.bank_a.motorStop(SH_Motor_Both, SH_Next_Action_Brake);
    evshield.bank_b.motorStop(SH_Motor_Both, SH_Next_Action_Brake);
    }
   
}



