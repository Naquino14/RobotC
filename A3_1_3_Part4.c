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
{                                     //Program begins, insert code within curly braces
	/*
		untilPotentiometerLessThan(2048, potentiometer);
		turnLEDOn(green);
		untilPotentiometerGreaterThan(2048, potentiometer);
		turnLEDOff(green);
		startMotor(leftMotor, 64);
		untilPotentiometerLessThan(2048, potentiometer);
		stopMotor(leftMotor);
		*/


	startMotor(leftMotor, 64);
		startMotor(rightMotor, 64);
		untilEncoderCounts(480, quad);
		stopMotor(leftMotor);
		stopMotor(rightMotor);
}
