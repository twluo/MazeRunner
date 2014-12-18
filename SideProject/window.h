#ifndef _WINDOW_H_
#define _WINDOW_H_
#include "Vector3.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include "cube.h"
#include "matrixTransform.h"
#include "SOIL.h"
#include <vector>
#include "Window.h"
#include "object.h"
#include "Matrix4.h"
#include "main.h"
#include "camera.h"
#include <time.h>
#include "shader.h"
#include "bpatch.h"
#include "Vector4.h"
#include "projection.h"
#include "viewport.h"
#include "bigPatch.h"
#include "bigPatch.h"
#include "BezierCurve.h"
#include "cube.h"
#include "matrixTransform.h"

#define M_PI 3.14159265358979323846
class Window	  // OpenGL output window related routines
{
  public:
    static int width, height; 	            // window size
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
	static void load();
	static void keyboardCallback(unsigned char, int, int);
	static void keyboardRelease(unsigned char, int, int);
	static void funcKeyboardCallback(int, int, int);
	static void funcMouseCallback(int, int, int, int);
	static void funcMouseMovement(int, int);
	static void setMatrix(Matrix4, Matrix4);
	static void setMatrix(Matrix4);
	static void loadTextures();
	static void loadCharacter();
};

#endif

