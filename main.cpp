#include <iostream>
// the day is 11/8/2026 and i know this program is gonna fuck me in the brain
// this is 11/8/2026 still?! and i was right lol
// sorry for swearing


class sphere_mesh
{
public:
	float vec3[3] = { 0.0f, 0.0f, 0.0f }; // x, y, z
	float ballX = 0.0f;
	float ballY = 0.0f;
	float ballZ = 0.0f;

	// ordered from biggest to smallest in terms of variable size
	// 3D vector for the ball's position and speed also ordered from x, y, z (ue5, blender and rockstar games format)
	// vec3[0] = 0.0f; // x axis
	// vec3[1] = 0.0f; // y axis
	// vec3[2] = 0.0f; // z axis

	// z axis variables
	float zheight = 0.0f;
	float zspeed = 0.0f;
	float airDensity = 1.225f; // kg/m^3, density of air at sea level
	float dragCoefficient = 0.47f;
	float dragForce = 0.0f;
	float currentAcceleration = 0.0f;
	// y axis variables
	float yspeedbase = 0.0f;
	float yspeed = 0.0f;
	char ydirection = 'f';
	// x axis variables
	float xspeed = 0.0f;
	float xspeedbase = 0.0f;
	char xdirection = 'r';
	// weight and size variables
	float mass = 0.43f; // mass of the ball in kg, not used in this program but could be used for future calculations
	float radius = 0.11f; // radius of the ball in meters, not used in this program but could be used for future calculations (matches weight to a standard soccer ball)
	float area = 0.038f; // area of a standard soccer ball calculated with pi * r^2, not used in this program but could be used for future calculations
	float restitution = 0.8f; // coefficient of restitution for a standard soccer ball, not used in this program but could be used for future calculations
	float frictionCoefficient = 0.5f; // coefficient of friction for a standard soccer ball, not used in this program but could be used for future calculations
	float stiffness = 1000.0f; // stiffness of a standard soccer ball, not used in this program but could be used for future calculations
	float floorLevel = 0.0f; // z level of the floor, not used in this program but could be used for future calculations
	float compression = 0.0f; // compression of the ball, not used in this program but could be used for future calculations
	float springforce = 0.0f;
	// rotation variables
	float pitch = 0.0f;
	float pitchSpeed = 0.0f;
	float yaw = 0.0f;
	float yawSpeed = 0.0f;
	float roll = 0.0f;
	float rollSpeed = 0.0f;

	void inputSphereInfo(float vec3[3])
	{

		std::cout << "Enter the ball's mass in kilograms: ";
		std::cin >> mass;
		std::cout << "Enter the ball's radius in meters: ";
		std::cin >> radius;
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
		std::cout << "Enter the Floor Level (z axis): ";
		std::cin >> floorLevel;
		std::cout << "Enter the Stiffness: ";
		std::cin >> stiffness;
		std::cout << "Enter the Friction: ";
		std::cin >> frictionCoefficient;

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

		area = 3.14159f * radius * radius;
	}

	void logSphereInfo(float timePassed, float gravity, float dt)
	{
		dragForce = 0.5f * airDensity * dragCoefficient * area * (zspeed * zspeed);
		compression = ballZ - (floorLevel - radius);

		if (compression < 0.0f) {
			compression = 0.0f;
		}

		springforce = stiffness * compression;
		currentAcceleration = gravity - (dragForce / mass) - (springforce / mass);
		zspeed = zspeed + (currentAcceleration * dt);

		if (compression > 0.0f) {
			xspeed = xspeed - (frictionCoefficient * gravity * dt);
			yspeed = yspeed - (frictionCoefficient * gravity * dt);

			// only slows the spin down when touching the floor!
			pitchSpeed = pitchSpeed - (frictionCoefficient * gravity * dt);
			rollSpeed = rollSpeed - (frictionCoefficient * gravity * dt);
		}
		// Update the cube's position based on the current speed and time passed
		ballX = ballX + (xspeed * dt);
		ballY = ballY + (yspeed * dt);
		ballZ = ballZ + (zspeed * dt);

		// Update the cube's rotation angles based on the current spin speeds
		pitch = pitch + (pitchSpeed * dt);
		yaw = yaw + (yawSpeed * dt);
		roll = roll + (rollSpeed * dt);

		std::cout << "Time: " << timePassed << "s, Ball Position: ( X: " << ballX << ", Y: " << ballY << ", Z: " << ballZ << ") | Speeds: (X: " << xspeed << ", Y: " << yspeed << ", Z: " << zspeed << ") | Compression: " << compression << " | Rotation: (X: " << pitch << ", Y: " << yaw << ", Z: " << ")\n";
	}

	void dectectFloor()
	{
		if (ballZ >= floorLevel - radius)
		{
			zspeed = -zspeed * restitution; // reverse the z speed and apply the coefficient of restitution
		}
	}
};

class cube_mesh
{
public:
	float vec3[3] = { 0.0f, 0.0f, 0.0f }; // x, y, z
	float cubeX = 0.0f;
	float cubeY = 0.0f;
	float cubeZ = 0.0f;

	// ordered from biggest to smallest in terms of variable size
	// 3D vector for the cube's position and speed also ordered from x, y, z (ue5, blender and rockstar games format)
	// vec3[0] = 0.0f; // x axis
	// vec3[1] = 0.0f; // y axis
	// vec3[2] = 0.0f; // z axis

	// z axis variables
	float zheight;
	float zspeed = 0.0f;
	float airDensity = 1.225f; // kg/m^3, density of air at sea level
	float dragCoefficient = 1.05f;
	float dragForce = 0.0f;
	float currentAcceleration = 0.0f;
	// y axis variables
	float yspeedbase;
	float yspeed;
	char ydirection;
	// x axis variables
	float xspeed;
	float xspeedbase;
	char xdirection;
	// weight and size variables
	float mass = 0.43f; // mass of the ball in kg, not used in this program but could be used for future calculations
	float sidelength = 0.11f; // radius of the ball in meters, not used in this program but could be used for future calculations (matches weight to a standard soccer ball)
	float area = 0.038f; // area of a standard soccer ball calculated with pi * r^2, not used in this program but could be used for future calculations
	float restitution = 0.8f; // coefficient of restitution for a standard soccer ball, not used in this program but could be used for future calculations
	float frictionCoefficient = 0.5f; // coefficient of friction for a standard soccer ball, not used in this program but could be used for future calculations
	float stiffness = 1000.0f; // stiffness of a standard soccer ball, not used in this program but could be used for future calculations
	float floorLevel = 0.0f; // z level of the floor, not used in this program but could be used for future calculations
	float compression = 0.0f; // compression of the ball, not used in this program but could be used for future calculations
	float springforce = 0.0f;

	// rotation variables
	float pitch = 0.0f;
	float pitchSpeed = 0.0f;
	float yaw = 0.0f;
	float yawSpeed = 0.0f;
	float roll = 0.0f;
	float rollSpeed = 0.0f;

	void inputCubeInfo(float vec3[3])
	{

		std::cout << "Enter the cubes's mass in kilograms: ";
		std::cin >> mass;
		std::cout << "Enter the cubes's side length in meters: ";
		std::cin >> sidelength;
		std::cout << "How many meters above ground do you want to drop the object from(z axis): ";
		std::cin >> zheight;
		std::cout << "What speed will the cube be traveling at (y axis): ";
		std::cin >> yspeedbase;
		std::cout << "Will the cube be traveling back or forward (f = forward b = backward): ";
		std::cin >> ydirection;
		std::cout << "What speed will the cube be traveling at (x axis): ";
		std::cin >> xspeedbase;
		std::cout << "Will the cube be traveling left or right (l = left r = right): ";
		std::cin >> xdirection;
		std::cout << "Enter the Floor Level (z axis): ";
		std::cin >> floorLevel;
		std::cout << "Enter the Stiffness: ";
		std::cin >> stiffness;
		std::cout << "Enter the Friction: ";
		std::cin >> frictionCoefficient;

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

		area = sidelength * sidelength;
	}

	void logCubeInfo(float timePassed, float gravity, float dt)
	{
		dragForce = 0.5f * airDensity * dragCoefficient * area * (zspeed * zspeed);
		compression = cubeZ - (floorLevel - (sidelength * 0.5f));

		if (compression < 0.0f) {
			compression = 0.0f;
		}

		springforce = stiffness * compression;
		currentAcceleration = gravity - (dragForce / mass) - (springforce / mass);
		zspeed = zspeed + (currentAcceleration * dt);

		if (compression > 0.0f) {
			xspeed = xspeed - (frictionCoefficient * gravity * dt);
			yspeed = yspeed - (frictionCoefficient * gravity * dt);

			// only slows the spin down when touching the floor!
			pitchSpeed = pitchSpeed - (frictionCoefficient * gravity * dt);
			rollSpeed = rollSpeed - (frictionCoefficient * gravity * dt);
		}

		// Update the cube's position based on the current speed and time passed
		cubeX = cubeX + (xspeed * dt);
		cubeY = cubeY + (yspeed * dt);
		cubeZ = cubeZ + (zspeed * dt);

		// Update the cube's rotation angles based on the current spin speeds
		pitch = pitch + (pitchSpeed * dt);
		yaw = yaw + (yawSpeed * dt);
		roll = roll + (rollSpeed * dt);

		std::cout << "Time: " << timePassed << "s, Cube's Position: ( X: " << cubeX << ", Y: " << cubeY << ", Z: " << cubeZ << ") | Speeds: (X: " << xspeed << ", Y: " << yspeed << ", Z: " << zspeed << ") | Compression: " << compression << " | Rotation: (X: " << pitch << ", Y: " << yaw << ", Z: " << roll << ")\n";
	}


	void dectectFloor()
	{
		if (cubeZ >= floorLevel - (sidelength * 0.5f))
		{
			zspeed = -zspeed * restitution; // reverse the z speed and apply the coefficient of restitution
		}
	}
};



int main()
{
	// base movement + calculation variables
	float gravity = 9.81f;
	float dt = 0.00606f; // time step in seconds, im so happy im finally getting proffesional! (this is from ue5, inter alia)
	float timePassed = 0.0f;

	sphere_mesh sphere;
	sphere.inputSphereInfo(sphere.vec3);
	//cube_mesh cube;
	//cube.inputCubeInfo(cube.vec3);

	while (1)
	{
		sphere.logSphereInfo(timePassed, gravity, dt);

		//cube.logCubeInfo(timePassed, gravity, dt);

		timePassed += dt;

		if (timePassed > 5.0f) { break;}

	}
	std::cin.get(); // wait for user input before closing the console window
}
