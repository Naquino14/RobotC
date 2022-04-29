#pragma config(Sensor, in1,    leftLineSensor, sensorLineFollower)
#pragma config(Sensor, in2,    rightLineSensor, sensorLineFollower)
#pragma config(Sensor, dgtl1,  greenLED,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  redLED,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl8,  button,         sensorTouch)
#pragma config(Sensor, dgtl9,  sonar,          sensorSONAR_inch)
#pragma config(Motor,  port4,           leftMotor,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex393_MC29, openLoop, reversed)
// Compiler pragma preprocessor directives to map robot sensors and motors to ports and variables.

// threshold for the robot's line followers
int thresh = 1875;

// 																									==================== main methods and subroutines ====================

bool SeeLine(short lineSensor)											// This function returns true or false wether the inputted line sensor sees a line or not
{ 																									// the parameter for the line follower is a short because sensor variables are just 16 bit
	return !(SensorValue(lineSensor) < thresh); 			// addresses mapped to certain ports thanks to the #pragma preprocessor directives. If the read value is less than the threshold,
}																										// the function returns false because it cannot see a line otherwise it does see a line, and returns true.

bool TooClose(float dist)														// this function returns true or false wether or not the sonar is a
{																										// certain inputted distance away from a wall.
	return SensorValue(sonar) < dist;									// If the read value from the sonar in inches is less than the inputted amount "dist" or the sensor the function returnes true
} 																									// otherwise the robot is too far away from the wall when the function was called, and it returns false.

void TurnAround(bool right, int speed)							// This method is a subroutine to tell the robot to move its wheels in opposite directions
{																										// in an inputted speed and direction.
	if (right)																				// Having true as the first argument,
	{
			startMotor(leftMotor, speed);									// Tells the robot to move its left wheel at the speed inputted into the second argument
			startMotor(rightMotor, speed * -1); 					// And the right motor spins at that same speed in the opposite direction.
	}																									// The result is that the robot turns right.
	else																							// Otherwise
	{
		startMotor(leftMotor, speed * -1);							// The robot moves its left motor at the speed inputted into the second argument, but in reverse
		startMotor(rightMotor, speed);									// and the right motor spins in that same speed
	}																									// resulting in the robot spinning left.
}

void StopMotors()																		// This method is simply a shortcut to stop all the motors
{
	stopMotor(leftMotor);															// Stops the left motor
	stopMotor(rightMotor);														// Stops the right motor
}

void StartMotors(int speed)													// This method is simply a shortcut to
{																										// start all the motors at a given inputted speed
	startMotor(leftMotor, speed); 										// Starts the left motor at the inputted speed
	startMotor(rightMotor, speed);										// Starts the right motor at the inputted speed
}


// 																									==================== routines ====================


void StartingTask()																	// This method is the first routine that the robot executes,
{																										// Its purpose is to prepare the robot and align it to carry cargo along a path.
	StartMotors(127);																	// It first starts the robots motors,
	do																								// and initiates a do-while loop,
		waitInMilliseconds(5);													// where what it does is wait 5 milliseconds,
	while(!TooClose(16));															// While the robot IS NOT too close to 16 inches away from any object

	StopMotors();																			// Once the robot is within 16 inches, it stops all motors
	TurnAround(true, 127);														// Starts to turn around to the right.
	wait(2);																					// The code then hangs for two seconds
	do																								// before initiating another do-while loop
		waitInMilliseconds(5);													// where it waits 5 milliseconds
	while (!SeeLine(rightLineSensor)); 								// while the robot does not see a line on the right line sensor.
																										// This is to align the robot with the path that it needs to take
	StopMotors();																			// The robot then stops its motors and waits for its next routine
}

void FollowLineTask()																// This method is the second routine that the robot executes,
{																										// its purpose is to get the robot to follow a path on the floor.
	StartMotors(65);																	// First, it starts the motors at half speed
	clearTimer(T1);																		// anc clears the timer
	while (true)																			// and initiates an infinite loop
	{																									// where it does all of the following...
		if (time1[T1] >= (10 * 1000) && TooClose(10))		// We used a combo of open and closed loop here because our robot would
			break;																				// randomly stop .5 - 1 second after we start this task.
		if (SeeLine(rightLineSensor))										// If the robot sees a line on the right line sensor
		{
			startMotor(leftMotor, 80);										// it speeds up the left motor,
			stopMotor(rightMotor);												// and stops the right one, resulting in the robot turning left.
		} else if (SeeLine(leftLineSensor)) 						// Otherwise, and if the robot sees a line on the left line sensor
		{
			startMotor(rightMotor, 80);										// It speeds up the right motor,
			stopMotor(leftMotor);													// and stops the left one.
		} else																					// Otherwise, if neither of those conditions are met, the robot is on path
				StartMotors(65);														// and it resets the speed of its motors to 50% once more
	} 																								//
	StopMotors();																			//	The robot then stops its motors and waits for its next routine
}

// 																									==================== Entrypoint ====================

task main()																					// This is the robots code executing entrypoint.
{
	while(true)																				// Initiate an infinite loop
	{
		untilBump(button);															// The first thing in the major loop is to hang the code intil the button is pressed
		turnLEDOn(greenLED);														// Turn on the green LED to indicate that the robot is enabled.
		StartingTask();																	// If the code execution is still here, that means that the routines havent been cancelled,so the robot starts its starting task,
		FollowLineTask();																// and then does its Follow Line task,
		StartMotors(-65);																// and tells the robot to turn around.
		wait(1);																				// the robot moves back for 1 second,
		StopMotors();																		// and stops the motors.
		turnLEDOn(redLED);															// If and when the robot breaks out of the major loop, the code execution falls out to here,
		turnLEDOff(greenLED);														// and turns the red LED on to indicate it has stopped, and the green LED off.
	}																									// and the process is repeated.
}
