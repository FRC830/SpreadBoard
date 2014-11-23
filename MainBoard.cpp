#include "WPILib.h"
#include "Gamepad.h"
#include <cmath>

class SpreadBoard : public IterativeRobot{
	
	static const int MOTOR_ONE = 1;
	static const int MOTOR_TWO = 2;
	static const int MOTOR_THREE = 3;
	
	
	
	
	Victor * motor_1;
	Victor * motor_2;
	Victor * motor_3;
	Gamepad * pilot;
	
	
	
void SpreadBoard::RobotInit() {
	
	motor_1 = new Victor(MOTOR_ONE);
	motor_2 = new Victor(MOTOR_TWO);
	motor_3 = new Victor(MOTOR_THREE);
	
	pilot = new Gamepad(1);
}


void SpreadBoard::DisabledInit() {
}


void SpreadBoard::DisabledPeriodic() {
}


void SpreadBoard::AutonomousInit() {
}


void SpreadBoard::AutonomousPeriodic() {
}


void SpreadBoard::TeleopInit() {
}


void SpreadBoard::TeleopPeriodic() {
	
	if (pilot->GetNumberedButton(3)){
		motor_1->Set(1.0);
	} else {
		motor_1->Set(0.0);
	}
	if (pilot->GetNumberedButton(4)){
		motor_2->Set(1.0);
	} else {
		motor_2->Set(0.0);
	}
	if (pilot->GetNumberedButton(2)){
		motor_3->Set(1.0);
	} else {
		motor_3->Set(0.0);
	}
}


void SpreadBoard::TestInit() {
}


void SpreadBoard::TestPeriodic() {
}
};
START_ROBOT_CLASS(SpreadBoard);

