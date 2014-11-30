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
	ADXL345_I2C * accelerometer;
	PIDController * pid;
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
		encoder->SetDistancePerPulse(1.0 / 64.0); //gives number of rotations; 1 rotation = 64 pulses
		encoder->SetPIDSourceParameter(Encoder::kRate);
		encoder->Start();
				
		gyro = new Gyro(GYRO_ANALOG);
		gyro->SetSensitivity(0.007f); //=7 mV/degree/sec
		
		accelerometer = new ADXL345_I2C(1); //1 is the digital module??
		
		pid = new PIDController(0.1, 0.0, 0.0, encoder, motor_1);
		
		lcd = DriverStationLCD::GetInstance();
	}
	
	
	void DisabledInit() {
	}
	
	
	void DisabledPeriodic() {
		lcd->Clear();
	}
	
	
	void AutonomousInit() {
	}
	
	
	void AutonomousPeriodic() {
	}
	
	
	void TeleopInit() {
	}
	
	double clamp(double speed, double maxMagnitude){
		if(fabs(speed) <= maxMagnitude)
			return 0;
		return speed;
	}
	
	void TeleopPeriodic() {
		//motor_1->Set(clamp(pilot->GetLeftY(), 0.1));
		motor_2->Set(clamp(pilot->GetLeftX(), 0.1));
		motor_3->Set(clamp(pilot->GetRightY(), 0.1));
		
		float angle = gyro->GetAngle();
		double rate = encoder->GetRate() * 60.0; //rpm
		
		lcd->PrintfLine(DriverStationLCD::kUser_Line1, "gyro: %f", angle);
		lcd->PrintfLine(DriverStationLCD::kUser_Line2, "angle: %d", NormalizedAngle(angle));
		lcd->PrintfLine(DriverStationLCD::kUser_Line3, "enc: %d", encoder->Get());
		lcd->PrintfLine(DriverStationLCD::kUser_Line4, "rpm: %d", (int) (rate + 0.5));
		lcd->PrintfLine(DriverStationLCD::kUser_Line5, "accel: %f", accelerometer->GetAccelerations().XAxis);
		
		
		lcd->UpdateLCD();
	}
		
	void TestInit() {
	}
	
	
	void TestPeriodic() {
	}
};
START_ROBOT_CLASS(SpreadBoard);

