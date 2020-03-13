//obstacle avoiding bot


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
        if (millis() % 1000 < 3) {
            Serial.println("Press GO button to continue");
        }
    }


    // reset motors.

    evshield.bank_a.motorReset();
    evshield.bank_b.motorReset();

 
}

void
loop()                          
{
  int distance;
  distance = myUS.getDist();
  if(distance > 10){
     evshield.bank_a.motorRunUnlimited(SH_Motor_Both, 
                                       SH_Direction_Forward,
                                      SH_Speed_Medium); 
  }
  else{
  evshield.bank_b.motorStop(SH_Motor_Both, SH_Next_Action_Brake);
  evshield.bank_b.motorRunRotations(SH_Motor_Both, 
                     SH_Direction_Reverse,
                     SH_Speed_Medium, 
                     rotations, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);

  delay(500);
  evshield.bank_b.motorRunRotations(SH_Motor_1, 
                     SH_Direction_Forward,
                     SH_Speed_Medium, 
                     rotations, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
  
  delay(500);}

}
