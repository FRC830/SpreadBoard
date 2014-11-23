#include "WPILib.h"
#include "Gamepad.h"
#include <cmath>

class PracticeBoardCode : public IterativeRobot
{
	static const int X_BUTTON = 1;
	static const int L_SHOULDER = 5;
	static const int R_SHOULDER = 6;
	
	static const int SUPER_LASER_PWM = 8;
	static const int CHAINSAW_CANNON_PWM = 9;
	static const int MARSHMALLOW_GUN_PWM = 7;
	
	Victor * super_laser;
	Victor * chainsaw_cannon;
	Victor * marshmallow_gun;
	
	Gamepad * pilot;
	
	DriverStationLCD * lcd;
	
public:
	
	/********************************** Init Routines *************************************/
	PracticeBoardCode(void) {
		
	}
	
	
	void RobotInit(void) {
		super_laser = new Victor(SUPER_LASER_PWM);
		chainsaw_cannon = new Victor(CHAINSAW_CANNON_PWM);
		marshmallow_gun = new Victor (MARSHMALLOW_GUN_PWM);
		
		pilot = new Gamepad(1);
		
		lcd = DriverStationLCD::GetInstance();
	}
	
	float clamp(float input, float min_mag){
		if (abs(input) > min_mag){
			return input;
		} else {
			return 0.0f;
		}
		
	}
	
	void DisabledInit(void) {
	}

	void AutonomousInit(void) {
	}

	void TeleopInit(void) {
		
	}

	/********************************** Periodic Routines *************************************/
	
	void DisabledPeriodic(void)  {
		lcd->PrintfLine(DriverStationLCD::kUser_Line1, "disabled");
		lcd->UpdateLCD();
	}

	void AutonomousPeriodic(void) {
	
	}

	
	void TeleopPeriodic(void) {
		if (pilot->GetNumberedButton(X_BUTTON)) {
			super_laser->Set(1.0);
		} else {
			super_laser->Set(0.0);
		}
		
		float left_x = pilot->GetLeftX();
		left_x = clamp(left_x, 0.05);
		chainsaw_cannon->Set(left_x);
		
		if (pilot->GetNumberedButton(L_SHOULDER) 
				|| pilot->GetNumberedButton(R_SHOULDER)){
			marshmallow_gun->Set(1.0);
		} else {
			marshmallow_gun->Set(0.0);
		}
		
		lcd->PrintfLine(DriverStationLCD::kUser_Line1, "hello worldX");
		lcd->UpdateLCD();
	} 
			
};

START_ROBOT_CLASS(PracticeBoardCode);
