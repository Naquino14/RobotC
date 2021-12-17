#pragma config(Sensor, in1,    lineFollower,   sensorLineFollower)
#pragma config(Sensor, in2,    potentiometer,  sensorPotentiometer)
#pragma config(Sensor, in3,    lightSensor,    sensorReflection)
#pragma config(Sensor, dgtl1,  limitSwitch,    sensorTouch)
#pragma config(Sensor, dgtl2,  bumpSwitch,     sensorTouch)
#pragma config(Sensor, dgtl3,  quad,           sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  sonar,          sensorSONAR_inch)
#pragma config(Sensor, dgtl12, green,          sensorLEDtoVCC)
#pragma config(Motor,  port1,           flashlight,    tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           rightMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           servoMotor,    tmotorServoStandard, openLoop)

/*
  Project Title:
  Team Members:
  Date:
  Section:


  Task Description:


  Pseudocode:

*/

task main()
{
	int lfThresh = (130 + 2800 ) / 2;
	/*
	while(true)
		{
			setServo(servoMotor, 127);
			untilDark(lfThresh, lineFollower);
			setServo(servoMotor, -127);
			untilLight(lfThresh, lineFollower);
		}*/
	/*
	startMotor(leftMotor, 63);
	startMotor(rightMotor, 63);
	untilSonarLessThan(20,sonar);
	stopMotor(leftMotor);
	stopMotor(rightMotor);
	turnLEDOn(green);
	wait(6.25);
	turnLEDOff(green);*/

	untilSonarLessThan(20, sonar);
	startMotor(leftMotor, 63);
	startMotor(rightMotor, 63);
	untilSonarGreaterThan(25, sonar);
	stopMotor(leftMotor);
	stopMotor(rightMotor);
	}
