#include "WPILib.h"
#include "Gamepad.h"
#include <cmath>

class SpreadBoard : public IterativeRobot{
	
	static const int MOTOR_ONE = 1;
	static const int MOTOR_TWO = 2;
	static const int MOTOR_THREE = 3;
	
	static const int GYRO_ANALOG = 1;
	
	static const int ENCODER_A = 2;
	static const int ENCODER_B = 3;
	
	Gyro * gyro;
	Victor * motor_1;
	Victor * motor_2;
	Victor * motor_3;
	Gamepad * pilot;
	Encoder * encoder;
	
	DriverStationLCD * lcd;
	
	
	int NormalizedAngle(float angle){
		int i_angle = (int) angle;
		if (i_angle >= 0) {
			return i_angle % 360;
		} else {
			return 360 + i_angle % 360;
		}
	}
	
	void RobotInit() {
		
		motor_1 = new Victor(MOTOR_ONE);
		motor_2 = new Victor(MOTOR_TWO);
		motor_3 = new Victor(MOTOR_THREE);
		
		pilot = new Gamepad(1);
		
		encoder = new Encoder(ENCODER_A, ENCODER_B);
		encoder->Start();
				
		gyro = new Gyro(GYRO_ANALOG);
		gyro->SetSensitivity(0.007f); //=7 mV/degree/sec
		
		lcd = DriverStationLCD::GetInstance();
	}
	
	
	void DisabledInit() {
	}
	
	
	void DisabledPeriodic() {
	}
	
	
	void AutonomousInit() {
	}
	
	
	void AutonomousPeriodic() {
	}
	
	
	void TeleopInit() {
	}
	
	
	void TeleopPeriodic() {
		motor_1->Set(pilot->GetLeftY());
		motor_2->Set(pilot->GetLeftX());
		motor_3->Set(pilot->GetRightY());
		
		float angle = gyro->GetAngle();
		
		lcd->PrintfLine(DriverStationLCD::kUser_Line1, "gyro: %f", angle);
		lcd->PrintfLine(DriverStationLCD::kUser_Line2, "angle: %d", NormalizedAngle(angle));
		lcd->PrintfLine(DriverStationLCD::kUser_Line3, "enc: %d", encoder->Get());

		
		lcd->UpdateLCD();
	}
		
	void TestInit() {
	}
	
	
	void TestPeriodic() {
	}
};
START_ROBOT_CLASS(SpreadBoard);

