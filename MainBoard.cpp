#include "WPILib.h"
#include "Gamepad.h"
#include <cmath>

class SpreadBoard : public IterativeRobot{
	
	static const int MOTOR_ONE = 1;
	static const int MOTOR_TWO = 2;
	static const int MOTOR_THREE = 3;
	
	static const int GYRO_ANALOG = 1;
	
	Gyro * gyro;
	Victor * motor_1;
	Victor * motor_2;
	Victor * motor_3;
	Gamepad * pilot;
	
	DriverStationLCD * lcd;
	
void SpreadBoard::RobotInit() {
	
	motor_1 = new Victor(MOTOR_ONE);
	motor_2 = new Victor(MOTOR_TWO);
	motor_3 = new Victor(MOTOR_THREE);
	
	pilot = new Gamepad(1);
	
	gyro = new Gyro(GYRO_ANALOG);
	gyro->SetSensitivity(0.007f); //=7 mV/degree/sec
	
	lcd = DriverStationLCD::GetInstance();
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
	motor_1->Set(pilot->GetLeftY());
	motor_2->Set(pilot->GetLeftX());
	motor_3->Set(pilot->GetRightY());
	
	float angle = gyro->GetAngle();
	lcd->PrintfLine(DriverStationLCD::kUser_Line1, "angle: %f", angle);
	
	lcd->UpdateLCD();
}
	
void SpreadBoard::TestInit() {
}


void SpreadBoard::TestPeriodic() {
}
};
START_ROBOT_CLASS(SpreadBoard);

