// Compiler pragma preprocessor directives to map robot sensors and motors to ports and variables.
#pragma config(Sensor, in1,    leftLineSensor, sensorLineFollower)
#pragma config(Sensor, in2,    rightLineSensor, sensorLineFollower)
#pragma config(Sensor, dgtl1,  greenLED,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  redLED,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl8,  button,         sensorTouch)
#pragma config(Sensor, dgtl9,  sonar,          sensorSONAR_inch)
#pragma config(Motor,  port4,           leftMotor,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex393_MC29, openLoop, reversed)


// threshold for the robot's line followers
int lineFollowerThresh = 1875;

// ==================== main methods and subroutines ====================

																										// This function returns true or false wether the inputted line sensor sees a line or not
bool SeeLine(short lineSensor)											// the parameter for the line follower is a short because sensor variables are just 16 bit
{ 																									// addresses mapped to certain ports thanks to the #pragma preprocessor directives.
	if (SensorValue(lineSensor) < lineFollowerThresh) // If the read value is less than the threshold,
		return false; 																	// the function returns false because it cannot see a line
	else 																							// otherwise
		return true; 																		// it does see a line, and returns true.
}

bool TooClose(float dist)					// this function returns true or false wether or not the sonar is a
{																	// certain inputted distance away from a wall.
	if (SensorValue(sonar) < dist)	// If the read value from the sonar in inches is less than the inputted amount "dist" or the sensor
		return true;									// the function returnes true
	else														// otherwise
		return false;									// the robot is too far away from the wall when the function was called, and it returns false
}

void TurnAround(bool right, int speed)		// This method is a subroutine to tell the robot to move its wheels in opposite directions
{																					// in an inputted speed and direction.
	if (right)															// Having true as the first argument,
	{
			startMotor(leftMotor, speed);				// Tells the robot to move its left wheel at the speed inputted into the second argument
			startMotor(rightMotor, speed * -1); // And the right motor spins at that same speed in the opposite direction.
	}																				// The result is that the robot turns right.
	else																		// Otherwise
	{
		startMotor(leftMotor, speed * -1);		// The robot moves its left motor at the speed inputted into the second argument, but in reverse
		startMotor(rightMotor, speed);				// and the right motor spins in that same speed
	}																				// resulting in the robot spinning left.
}

void StopMotors()					// This method is simply a shortcut to stop all the motors
{
	stopMotor(leftMotor);		// Stops the left motor
	stopMotor(rightMotor);	// Stops the right motor
}

void StartMotors(int speed)				// This method is simply a shortcut to
{																	// start all the motors at a given inputted speed
	startMotor(leftMotor, speed); 	// Starts the left motor at the inputted speed
	startMotor(rightMotor, speed);	// Starts the right motor at the inputted speed
}


// ==================== routines ====================


void StartingTask()										// This method is the first routine that the robot executes,
{																			// Its purpose is to prepare the robot and align it to carry cargo along a path.
	StartMotors(127);										// It first starts the robots motors,
	do																	// and initiates a do-while loop,
		waitInMilliseconds(5);						// where what it does is wait 5 milliseconds,
	while(!TooClose(16));								// While the robot IS NOT too close to 16 inches away from any object

	StopMotors();												// Once the robot is within 16 inches, it stops all motors
	TurnAround(true, 127);							// Starts to turn around to the right.
	wait(2);														// The code then hangs for two seconds
	do																	// before initiating another do-while loop
		waitInMilliseconds(5);						// where it waits 5 milliseconds
	while (!SeeLine(rightLineSensor)); 	// while the robot does not see a line on the right line sensor.
																			// This is to align the robot with the path that it needs to take
	StopMotors();												// The robot then stops its motors and waits for its next routine
}

void FollowLineTask()											// This method is the second routine that the robot executes,
{																					// its purpose is to get the robot to follow a path on the floor.
	StartMotors(65);												// First, it starts the motors at half speed
	do																			// and initiates a do-while loop
	{																				// where it does all of the following...
		if (SeeLine(rightLineSensor))					// If the robot sees a line on the right line sensor
		{
			startMotor(leftMotor, 80);					// it speeds up the left motor,
			stopMotor(rightMotor);							// and stops the right one, resulting in the robot turning left.
		} else if (SeeLine(leftLineSensor)) 	// Otherwise, and if the robot sees a line on the left line sensor
		{
			startMotor(rightMotor, 80);					// It speeds up the rigth motor,
			stopMotor(leftMotor);								// and stops the left one.
		} else																// Otherwise, if neither of those conditions are met, the robot is on path
				StartMotors(65);									// and it resets the speed of its motors to 50% once more
	} while (!TooClose(6));									// ... all while the robot is not too close to a wall
	StopMotors();														//	The robot then stops its motors and waits for its next routine
}

// ==================== Entrypoint ====================

task main()													// This is the robots code executing entrypoint.
{
	turnLEDOn(greenLED);							// Turn on the green LED to indicate that the robot is enabled.
	while(true)												// Initiate an infinite loop
	{
		untilBump(button);							// The first thing in the major loop is to hang the code intil the button is pressed
		int stopCounter = 0;						// The program then makes 2 local variables, a counter that is first set to 0
		bool breakFlag = false;					// and a boolean that is initially set to false.
		do 															// Next it initiates a do-while loop where it does all of the following...
		{
			if (stopCounter => 10)				// If the stop counter is more than or equal to 10
			{
				breakFlag = true;						// It sets the breakFlag to true,
				break;											// and breaks out of the do-while loop
			}
			stopCounter++;								// if the condition is not met, the counter gets incrimented by 1
			waitInMilliseconds(100);			// and the code hangs for 100 ms
		} while(SensorValue(button));   // ... all while the button is held
																		// the purpose of all of this is to be able to press and hold the button to stop the robot
		if (breakFlag)									// If the flag that we set before is true,
			break;												// The code execution breaks out of the major loop.
		StartingTask();									// If the code execution is still here, that means that the routines havent been cancelled,so the robot starts its starting task,
		FollowLineTask();								// and then does its Follow Line task,
	}																	// and the process is repeated.
	turnLEDOn(redLED);								// If and when the robot breaks out of the major loop, the code execution falls out to here,
	turnLEDOff(greenLED);							// and turns the red LED on to indicate it has stopped, and the green LED off.
}
