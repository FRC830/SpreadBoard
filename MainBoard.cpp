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
		encoder->SetReverseDirection(true);
		encoder->SetDistancePerPulse(1.0 / 64.0); //gives number of rotations; 1 rotation = 64 pulses
		encoder->SetPIDSourceParameter(Encoder::kRate);
		encoder->Start();
				
		gyro = new Gyro(GYRO_ANALOG);
		gyro->SetSensitivity(0.007f); //=7 mV/degree/sec
		
		accelerometer = new ADXL345_I2C(1); //1 is the digital module??
		
		pid = new PIDController(2.3, 0.0, 0.5, encoder, motor_1);
		pid->SetInputRange(0.0, 1.4); //approximate range of encoder values
		pid->SetOutputRange(0.0, 1.0); //valid victor inputs (we don't want to go backwards)
		pid->SetSetpoint(1.0f); //1 rps
		
		lcd = DriverStationLCD::GetInstance();
	}
	
	
	void DisabledInit() {
	}
	
	
	void DisabledPeriodic() {
		lcd->Clear();
		pid->Disable();
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
		
		pid->Enable();
		
		float angle = gyro->GetAngle();
		double rate = encoder->PIDGet(); //rps
		
		ADXL345_I2C::AllAxes accel = accelerometer->GetAccelerations();
		//convert from G's to ft/s^2 (1G = 32ft/s^2
		accel.XAxis *= 32.0;
		accel.YAxis *= 32.0;
		accel.ZAxis *= 32.0;
		double accel_mag = sqrt(pow(accel.XAxis, 2) + pow(accel.YAxis, 2) + pow(accel.ZAxis, 2));
		
		//lcd->PrintfLine(DriverStationLCD::kUser_Line1, "gyro: %f", angle);
		lcd->PrintfLine(DriverStationLCD::kUser_Line1, "angle: %d", NormalizedAngle(angle));
		//lcd->PrintfLine(DriverStationLCD::kUser_Line3, "enc: %d", encoder->Get());
		lcd->PrintfLine(DriverStationLCD::kUser_Line2, "rps: %f", rate);
		lcd->PrintfLine(DriverStationLCD::kUser_Line3, "spt: %f", pid->GetSetpoint());
		//lcd->PrintfLine(DriverStationLCD::kUser_Line3, "x: %d", (int) accel.XAxis);
		//lcd->PrintfLine(DriverStationLCD::kUser_Line4, "y: %d", (int) accel.YAxis);
		//lcd->PrintfLine(DriverStationLCD::kUser_Line5, "z: %d", (int) accel.ZAxis);
		lcd->PrintfLine(DriverStationLCD::kUser_Line6, "mag: %d", (int) accel_mag);
		
		
		
		lcd->UpdateLCD();
	}
		
	void TestInit() {
	}
	
	
	void TestPeriodic() {
	}
};
START_ROBOT_CLASS(SpreadBoard);

