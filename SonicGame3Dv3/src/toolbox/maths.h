#ifndef MATHS_H
#define MATHS_H

class Matrix4f;
class Vector3f;
class Camera;

#include <math.h>

#define M_PI 3.14159265358979323846


float toRadians(float);

float toDegrees(float);

/*
** Blank Matrix4f should have already been created. This function does not allocate any memory to matrix.
*/
void createTransformationMatrix(Matrix4f*, Vector3f*, float, float, float, float, float);

//Based on how sadx calculates rotations
void createTransformationMatrixSADX(Matrix4f*, Vector3f*, float, float, float, float);

void createViewMatrix(Matrix4f*, Camera*);

//Returns the difference between the two angles
//ang1 and ang2 should be in degrees
float compareTwoAngles(float ang1, float ang2);

int sign(float value);

//result needs to be array of 3 doubles
void rotatePoint(double result[],
	double a, double b, double c,
	double u, double v, double w,
	double x, double y, double z,
	double theta);

//angle in radians
Vector3f mapInputs3(float angle, float mag, Vector3f* VecC);

//in radians
Vector3f mapCamera(float yaw, float pitch, float mag, Vector3f* VecC);


Vector3f bounceVector(Vector3f* initialVelocity, Vector3f* surfaceNormal, float elasticity);

/**
* Calculate the x and z speeds relative to a plane based off
* the previous position you are coming in from
*
* @param xspd the x speed that you are going at before collision
* @param yspd the y speed that you are going at before collision
* @param zspd the z speed that you are going at before collision
* @param A the collision point on the triangle
* @param normal the normal of the triangle
*/
Vector3f calculatePlaneSpeed(float xspd, float yspd, float zspd, Vector3f* normal);

/** Returns the point on a sphere that has the given angles from the center
* @param angH in radians
* @param angV in radians
* @param radius
* @return
*/
Vector3f spherePositionFromAngles(float angH, float angV, float radius);

Vector3f projectOntoPlane(Vector3f* A, Vector3f* normal);

//returns uniform random float >= 0 and < 1
float random();

//normal distribution mean = 0, std dev = 1
float nextGaussian();

#endif