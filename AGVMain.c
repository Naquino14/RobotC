#pragma config(Sensor, in1,    leftLineSensor, sensorLineFollower)
#pragma config(Sensor, in2,    rightLineSensor, sensorLineFollower)
#pragma config(Sensor, dgtl1,  greenLED,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  redLED,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl8,  button,         sensorTouch)
#pragma config(Sensor, dgtl9,  sonar,          sensorSONAR_inch)
#pragma config(Motor,  port4,           leftMotor,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


int lineFollowerThresh = 1875;

// funcs

bool SeeLine(short lineSensor)
{
	if (SensorValue(lineSensor) < lineFollowerThresh)
		return false;
	else
		return true;
}

bool TooClose(float dist)
{
	if (SensorValue(sonar) < dist)
		return true;
	else
		return false;
}

void TurnAround(bool right, int speed)
{
	if (right)
	{
			startMotor(leftMotor, speed);
			startMotor(rightMotor, speed * -1);
	}
	else
	{
		startMotor(leftMotor, speed * -1);
		startMotor(rightMotor, speed);
	}
}

void StopMotors()
{
	stopMotor(leftMotor);
	stopMotor(rightMotor);
}

void StartMotors(int speed)
{
	startMotor(leftMotor, speed);
	startMotor(rightMotor, speed);
}


// tasks

void StartingTask()
{
	StartMotors(127);
	do
		waitInMilliseconds(5);
	while(!TooClose(12));

	StopMotors();
	TurnAround(true, 127);
	wait(2);
	do
		waitInMilliseconds(5);
	while (!SeeLine(rightLineSensor));

	StopMotors();
	startMotors(65);
}

void FollowLineTask()
{
	do
	{
		do // left line spotted
			startMotor(rightMotor, 50);
		while (SeeLine(leftLineSensor);

		do // rightlLine spotted
			startMotor(leftMotor, 50);
		while (SeeLine(rightLineSensor);

		waitInMilliseconds(10);
		StartMotors(65);

	} while (!TooClose(12));
}

task main()
{
	//startMotor(leftMotor, 65);
	bool enabledFlag = true;
	while(enabledFlag)
	{
		untilBump(button);
		//StartingTask();
		FollowLineTask();
	}



}