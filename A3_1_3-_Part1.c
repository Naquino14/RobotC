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



task main()
{
		/*
		untilBump(bumpSwitch);
		startMotor(rightMotor, 67);
		wait(5);
		stopMotor(rightMotor);


	untilBump(bumpSwitch);
	startMotor(rightMotor, 64);
	startMotor(leftMotor, 64);
	wait(0.4);
	untilBump(bumpSwitch);
	startMotor(rightMotor, -64);
	startMotor(leftMotor, -64);
	wait(3.5);
	stopMotor(rightMotor);
	stopMotor(leftMotor);

	turnLEDOn(green);
	untilPotentiometerGreaterThan(2048, potentiometer);
	turnLEDOff(green);
	startMotor(leftMotor, 63);
	wait(3.5);
	stopMotor(leftMotor);
	*/




}
