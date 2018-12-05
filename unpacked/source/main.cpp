#include "robot-config.h"

int auton = 1; //Autonomous selection

int velocityCoef = 1;

        //NOTE: wheelControl is used w/ degrees, not time
        void wheelStraight (int lDeg, int rDeg)
        {
            FrontLeft.startRotateFor(lDeg,rotationUnits::deg);
            FrontRight.startRotateFor(rDeg,rotationUnits::deg);
            BackLeft.startRotateFor(lDeg,rotationUnits::deg);
            BackRight.startRotateFor(rDeg,rotationUnits::deg);
        }
        //NOTE: wheelControl is used w/ degrees, not time

        //NOTE: Use this for when each wheel needs independent control
            void wheelTurn (int Fldeg, int Frdeg, int Bldeg, int Brdeg)
        {
          FrontLeft.startRotateFor(Fldeg,rotationUnits::deg,50,velocityUnits::pct);
          FrontRight.startRotateFor(Bldeg,rotationUnits::deg,50,velocityUnits::pct);
          BackLeft.startRotateFor(Fldeg,rotationUnits::deg,50,velocityUnits::pct);
          BackRight.startRotateFor(Brdeg,rotationUnits::deg,50,velocityUnits::pct);
        }



        //NOTE: puncherControl is used w/ degrees. 1000 degrees is about one shot
        void punchControl (int punchLdeg, int punchRdeg)
        {
            PuncherRight.startRotateFor(punchRdeg,rotationUnits::deg);
            PuncherLeft.startRotateFor(punchLdeg,rotationUnits::deg);
        }
        //NOTE: puncherControl is used w/ degrees. 1000 degrees is about one shot


        //NOTE: intakeControl is toggled, and has to be braked
        void intakeControl (int intakeTime)
        {
            Intake.spin(directionType::fwd);
        }
        void intakeReverse (int intakeTime)
        {
            Intake.spin(directionType::rev);
        }
        //NOTE: intakeControl is toggled, and has to be braked


        //NOTE: used to shorten brake function, retype for other brake types
        void wheelBrake()
        {
            FrontRight.stop(brakeType::coast);
            FrontLeft.stop(brakeType::coast);
            BackRight.stop(brakeType::coast);
            BackLeft.stop(brakeType::coast);
        }
        //NOTE: used to shorten brake function, retype for other brake types


        void handBrake()
        {
            FrontRight.stop(brakeType::hold);
            FrontLeft.stop(brakeType::hold);
            BackRight.stop(brakeType::hold);
            BackLeft.stop(brakeType::hold);
        }


void pre_auton( void ) {
    Brain.Screen.print("Program has started!");
    Brain.Screen.newLine();
    Brain.Screen.print("Make sure to reset puncher slip gear after each match.");
    Brain.Screen.newLine();
    Brain.Screen.print("Battery Capacity: %d\n", Brain.Battery.capacity());
    Brain.Screen.print("Battery Temperature: %d", Brain.Battery.temperature());
    Brain.Screen.newLine();
    Brain.Screen.setPenWidth(5);

    while(1 == 1)
    {
        if(Brain.Screen.pressing())
        {
            auton++;
            if(auton > 5)
            {
                auton = 1;
            }
        }
        Brain.Screen.printAt(50,120,"Auton Select: %d", auton);
        if(auton == 1)
        {
            Brain.Screen.printAt(50,150,"                                    ");
            Brain.Screen.printAt(50,150, "Auton Program: Blue Far");
        }
        else if(auton == 2)
        {
            Brain.Screen.printAt(50,150,"                                    ");
            Brain.Screen.printAt(50,150, "Auton Program: Blue Near");
        }
        else if(auton == 3)
        {
            Brain.Screen.printAt(50,150,"                                    ");
            Brain.Screen.printAt(50,150, "Auton Program: Red Far");
        }
        else if(auton == 4)
        {
            Brain.Screen.printAt(50,150,"                                    ");
            Brain.Screen.printAt(50,150, "Auton Program: Red Near");
        }
        else
        {
            Brain.Screen.printAt(50,150,"                                    ");
            Brain.Screen.printAt(50,150,"Auton Program: Brake");
        }


        task::sleep(500);
    }
}


void autonomous( void ) {
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(50,120,"                                    ");
  Brain.Screen.printAt(50,150,"                                    ");

  FrontLeft.setVelocity(200,velocityUnits::rpm);
  FrontRight.setVelocity(200,velocityUnits::rpm);
  BackLeft.setVelocity(200,velocityUnits::rpm);
  BackRight.setVelocity(200,velocityUnits::rpm);
  PuncherLeft.setVelocity(200,velocityUnits::rpm);
  PuncherRight.setVelocity(200,velocityUnits::rpm);
  Intake.setVelocity(200,velocityUnits::rpm);

  switch(auton)
  {
      case 1: //BLUE FAR

          break;

      case 2: //BLUE NEAR
          wheelStraight(1150, 1150);
          task::sleep(2000);
          //Drive forward for six rotations of the wheels.
          //NOTE: Sequence of values is:
          /*
            FrontLeft degrees
            FrontRight degrees
            BackLeft degrees
            BackRight degrees
          */
          //times without puncher weight factored as of 11/26/18
          //Iterates the ball launcher once.
          //NOTE: Sequence of values is:
          /*
            PuncherLeft degrees
            PuncherRight degrees
          */
          //NOTE: Change the rotation unit? Revolutions might work better

          wheelStraight(-1150, -1150);
          task::sleep(1000);

          wheelTurn(-8500,8500,-8500,8500);
          task::sleep(1000);

          wheelStraight(1200, 1200);
          task::sleep(2000);
          wheelStraight(-120,-120);
          wheelTurn(-2250,2250,-2250,2250);
          wheelStraight(120, 120);
          intakeControl(1000);
          wheelStraight(100,100);
          wheelStraight(-250,-250);



          break;

      case 3: //RED FAR
          wheelStraight(360, 360);
          task::sleep(1000);
          wheelBrake();

          punchControl(1000, 1000);
          task::sleep(1000);

          wheelStraight(180, 180);
          task::sleep(1000);
          wheelBrake();
          break;

      case 4: //RED NEAR
          break;

      case 5:
          handBrake();
          break;

      default: //Error
          Brain.Screen.clearScreen();
          Brain.Screen.printAt(1,1,"Invalid Autonomous Selection");
          handBrake();
          break;
  }

    task::sleep(1000);
}

void usercontrol( void ) {
    int velocityVar = 200;


    PuncherLeft.setVelocity(velocityVar,velocityUnits::rpm);
    PuncherRight.setVelocity(velocityVar,velocityUnits::rpm);
    Intake.setVelocity(200,velocityUnits::rpm);
    Postscorer.setVelocity(100,velocityUnits::rpm);
    FrontLeft.setVelocity(velocityVar,velocityUnits::rpm);
    FrontRight.setVelocity(velocityVar,velocityUnits::rpm);
    BackLeft.setVelocity(velocityVar,velocityUnits::rpm);
    BackRight.setVelocity(velocityVar,velocityUnits::rpm);

    Brain.Screen.clearScreen();
    Brain.Screen.newLine();
    Brain.Screen.print("party rockers in the hou");
    Brain.Screen.newLine();
    Brain.Screen.print("se tonight");
    Brain.Screen.newLine();
    Brain.Screen.newLine();
    Brain.Screen.print("Make sure to reset puncher gear.");
  while (1){

    velocityVar = 200 / velocityCoef;
    /*
      NOTE: This doesn't work as of last time testing
      Might work now that it's inside loop
      Probably need to put other stuff in loop to work right.
    */


    //=======================Joystick / drive motor controls=======================
    FrontRight.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
    FrontLeft.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    BackRight.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
    BackLeft.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    //=======================Joystick / drive motor controls=======================


    //=======================Puncher motor controls=======================
    if(Controller1.ButtonR1.pressing())
    {
        PuncherLeft.spin(vex::directionType::rev);
        PuncherRight.spin(vex::directionType::fwd);
    }
    else if(Controller1.ButtonR2.pressing())
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
    //NOTE: Make sure to reset puncher after every match.


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
        Intake.stop(brakeType::coast);
    }
    //=======================Intake motor controls=======================


    //=======================Cap Flipper motor controls=======================
    if(Controller1.ButtonUp.pressing())
    {
        Postscorer.spin(vex::directionType::fwd);
    }
    else if(Controller1.ButtonDown.pressing())
    {
        Postscorer.spin(vex::directionType::rev);
    }
    else
    {
        Postscorer.stop(brakeType::coast);
    }
    //=======================Cap Flipper motor controls=======================


    //=======================Speed incrementing controls=======================
    if(Controller1.ButtonRight.pressing())
    {
        velocityCoef = 1;
    }

    if(Controller1.ButtonLeft.pressing())
    {
            velocityCoef = 2;
    }
    //=======================Speed incrementing controls=======================


    //======================="Handbrake-but-not-really" controls=======================
    if(Controller1.ButtonB.pressing())
    {
        handBrake();
    }
    //======================="Handbrake-but-not-really" controls=======================


    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
  }
}

int main() {
    pre_auton();

    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );

    Competition.drivercontrol( usercontrol );

    while(1) {

    vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }

}
