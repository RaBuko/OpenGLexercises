#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <fstream>

class Jajko
{
	double pi = 3.14159265359;
public:
	int model_jajka = 3;
	Jajko();
	~Jajko();
};

struct point
{
	float x;
	float y;
	float z;
};

