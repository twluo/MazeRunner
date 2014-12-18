#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Matrix4.h"
#include "main.h"
#include "object.h"
#include "Vector3.h"

using namespace std;

namespace Globals
{
  Object object;
  Shader *shader;
};

int main(int argc, char *argv[])
{
  float specular[]  = {0.0, 0.0, 0.0, 1.0};
  float shininess[] = {100.0};
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("Side Proejct! :O :O :O ");    	      // open window and set window title

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 

  glEnable(GL_NORMALIZE);

  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);
  glutKeyboardFunc(Window::keyboardCallback);
  glutKeyboardUpFunc(Window::keyboardRelease);
  glutMouseFunc(Window::funcMouseCallback);
  glutMotionFunc(Window::funcMouseMovement);
  //glutSetCursor(GLUT_CURSOR_NONE);
  glutSpecialFunc(Window::funcKeyboardCallback);
    
  // Initialize cube matrix:
  Globals::object.getMatrix().identity();
  Globals::shader = new Shader("perPixelShade.vert", "perPixelShade.frag", true);
  Window::load();
  glutMainLoop();
  return 0;
}

