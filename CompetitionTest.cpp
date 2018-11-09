#include "robot-config.h"

int auton = 0; //Autonomous selection

void pre_auton( void ) {
  // All activities that occur before the competition starts. Example: clearing encoders, setting servo positions,
    /*if (Brain.Screen.pressing())
    {
        auton++;
    }
    if (auton == 5)
        auton = 1;
    
    else if (auton == 1)
    {
        auton = 1;
        Brain.Screen.setCursor(1,1);
        Brain.Screen.setPenColor(color::blue);
        Brain.Screen.print("Auton is set to: [placeholder]");
    }
    else if (auton == 2)
    {
        auton = 2;
        Brain.Screen.setCursor(1,1);
        Brain.Screen.setPenColor(color::red);
        Brain.Screen.print("Auton is set to [placeholder]");
    }
    else if (auton == 3)
    {
        auton = 3;
        Brain.Screen.setCursor(1,1);
        Brain.Screen.setPenColor(color::green);
        Brain.Screen.print("Auton is set to [placeholder]");
    }
    else if (auton == 4)
    {
        auton = 4;
        Brain.Screen.setCursor(1,1);
        Brain.Screen.setPenColor(color::yellow);
        Brain.Screen.print("Auton is set to [placeholder]");
        */
}
    

void autonomous( void ) {
  // Insert autonomous user code here.
  FrontLeft.setVelocity(200,velocityUnits::rpm);
  FrontRight.setVelocity(200,velocityUnits::rpm);
  BackLeft.setVelocity(200,velocityUnits::rpm);
  BackRight.setVelocity(200,velocityUnits::rpm);
  PuncherLeft.setVelocity(200,velocityUnits::rpm);
  PuncherRight.setVelocity(200,velocityUnits::rpm);
  Intake.setVelocity(200,velocityUnits::rpm);
  CapFlipper.setVelocity(200,velocityUnits::rpm);
  /*switch (auton)
  {
    case 1:
        //g
        break;
    case 2:
        //o
        break;
    case 3:
        //o
        break;
    case 4:
        //d
        break;
    default:
        break;
  } */
    
    if(AutonSelect.value(percentUnits::pct) > 98)
    {
        FrontLeft.spin(vex::directionType::fwd);
        FrontRight.spin(vex::directionType::fwd);
        BackLeft.spin(vex::directionType::fwd);
        BackRight.spin(vex::directionType::fwd);
    }
    else if(AutonSelect.value(percentUnits::pct) < 97 || AutonSelect.value(percentUnits::pct) > 80)
    {
        FrontLeft.spin(vex::directionType::rev);
        FrontRight.spin(vex::directionType::rev);
        BackLeft.spin(directionType::rev);
        BackRight.spin(directionType::rev);
    }
    

    task::sleep(1000);
}

void usercontrol( void ) {
    FrontLeft.setVelocity(200,velocityUnits::rpm);
    FrontRight.setVelocity(200,velocityUnits::rpm);
    BackLeft.setVelocity(200,velocityUnits::rpm);
    BackRight.setVelocity(200,velocityUnits::rpm);
    PuncherLeft.setVelocity(200,velocityUnits::rpm);
    PuncherRight.setVelocity(200,velocityUnits::rpm);
    Intake.setVelocity(200,velocityUnits::rpm);
    CapFlipper.setVelocity(100,velocityUnits::rpm);
  while (1){
    //=======================Joystick / drive motor controls=======================
    FrontRight.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    FrontLeft.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
    BackRight.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    BackLeft.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
    //=======================Joystick / drive motor controls=======================
      
    
    //=======================Puncher motor controls======================= 
    if(Controller1.ButtonDown.pressing())
    {
        PuncherLeft.spin(vex::directionType::rev);
        PuncherRight.spin(vex::directionType::fwd);
    }
    else if(Controller1.ButtonUp.pressing())
    {
        PuncherLeft.spin(vex::directionType::fwd);
        PuncherRight.spin(vex::directionType::rev);
    }
    else
    {
        PuncherLeft.stop(brakeType::hold);
        PuncherRight.stop(brakeType::hold);
    }
    //=======================Puncher motor controls=======================  
      
      
    //=======================Intake motor controls=======================  
    if(Controller1.ButtonL1.pressing())
    {
        Intake.spin(vex::directionType::rev);
    }
    else if(Controller1.ButtonL2.pressing())
    {
        Intake.spin(vex::directionType::fwd);
    }
    else
    {
        Intake.stop(brakeType::hold);
    }
    //=======================Intake motor controls=======================
    
    
    //=======================Cap Flipper motor controls=======================  
    if(Controller1.ButtonR1.pressing())
    {
        CapFlipper.spin(vex::directionType::fwd);
    }
    else if(Controller1.ButtonR2.pressing())
    {
        CapFlipper.spin(vex::directionType::rev);
    }
    else
    {
        CapFlipper.stop(brakeType::hold);
    }
    //=======================Cap Flipper motor controls=======================
      
      
    //======================="Handbrake" controls=======================
    if(Controller1.ButtonB.pressing())
    {
        FrontRight.stop(brakeType::hold);
        FrontLeft.stop(brakeType::hold);
        BackRight.stop(brakeType::hold);
        BackLeft.stop(brakeType::hold);
    }
    //======================="Handbrake" controls=======================
      
      
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

int main() {
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
        int drive (int time, int power, int turn);
        
    Competition.drivercontrol( usercontrol );
                    
    while(1) {
    
        
    vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
    //Pot Code
    
    
}