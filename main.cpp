#include <iostream>
// the day is 11/8/2026 and i know this program is gonna fuck me in the brain
// sorry for swearing

float askPlacement(float vec3[3])
{
	// ordered from biggest to smallest in terms of variable size
	// 3D vector for the ball's position and speed also ordered from x, y, z (ue5, blender and rockstar games format)
	// vec3[0] = 0.0f; // x axis
	// vec3[1] = 0.0f; // y axis
	// vec3[2] = 0.0f; // z axis

	// z axis variables
	float zheight;
	float zspeedbase = 0.0f;
	// y axis variables
	float yspeedbase;
	float yspeed;
	char ydirection;
	// x axis variables
	float xspeed;
	float xspeedbase;
	char xdirection;

	std::cout << "How many meters above ground do you want to drop the object from(z axis): ";
	std::cin >> zheight;
	std::cout << "What speed will the ball be traveling at (y axis): ";
	std::cin >> yspeedbase;
	std::cout << "Will the ball be traveling back or forward (f = forward b = backward): ";
	std::cin >> ydirection;
	std::cout << "What speed will the ball be traveling at (x axis): ";
	std::cin >> xspeedbase;
	std::cout << "Will the ball be traveling left or right (l = left r = right): ";
	std::cin >> xdirection;

	// set the y speeds based on the direction input
	if (ydirection == 'f')
	{
		yspeed = yspeedbase;
	}
	else if (ydirection == 'b')
	{
		yspeed = -(yspeedbase);
	}
	else
	{
		std::cout << "Invalid input for y direction. Aborting Program." << std::endl;
		exit(0);
	}

	// set the x speeds based on the direction input
	if (xdirection == 'r')
	{
		xspeed = xspeedbase;
	}
	else if (xdirection == 'l')
	{
		xspeed = -(xspeedbase);
	}
	else
	{
		std::cout << "Invalid input for x direction. Aborting Program." << std::endl;
		exit(0);
	}
	
	vec3[0] = xspeed;
	vec3[1] = yspeed;
	vec3[2] = zheight;

	return vec3[3];
}

float timeToPass()
{
	float time = 0.0f;
	std::cout << "How long do you want to simulate the ball's motion for (in seconds): ";
	std::cin >> time;
	return time;
}

int main()
{
	// base movement variables
	float gravity = 9.81f;
	float vec3[3] = { 0.0f, 0.0f, 0.0f }; // x, y, z
	float ballX = 0.0f;
	float ballY = 0.0f;
	float ballZ = 0.0f;
	// calculation variables
	float dt = 0.00606f; // time step in seconds, im so happy im finally getting proffesional! (this is from ue5, inter alia)
	float timePassed = 0.0f;
	float totalTime = 0.0f;

	askPlacement(vec3);
	totalTime = timeToPass();

	while (timePassed <= totalTime)
	{

		ballX = vec3[0] * timePassed;
		ballY = vec3[1] * timePassed;
		ballZ = 0.5f * gravity * timePassed * timePassed;

		std::cout << "Time: " << timePassed << "s, Ball Position: ( X: " << ballX << ", Y: " << ballY << ", Z: " << ballZ << ")" << std::endl;
		timePassed += dt;
	}
	std::cin.get(); // wait for user input before closing the console window
}