#include "window.h"
using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
static float x = 0;
static float y = -1;
static float z = -6;
float position[] = { -10.0, 10.0, 10.0, 0.0 };	// lightsource position

//Directions
Vector4 ahead = Vector4(0, 0, -1, 0);
Vector4 side = Vector4(-1, 0, 0, 0);
//Camera
Vector3 e = Vector3(0, 7, 10);
Vector3 d = Vector3(0, 7, 9);
Vector3 up = Vector3(0, 1, 0);

//Belz Camera
Vector3 belzD = Vector3(0, 0, 0);
Vector3 belzUp = Vector3(0, 1, 0);
//Patch settings
Vector4 initial = Vector4(-4, 4, 0, 0);
Vector4 endV = Vector4(4, 4, 0, 0);
bpatch bPatch;
BezierCurve bCurve;

//Flags
int degree = 0;
int t = 0;
bool forw = true;
bool cam = false;
bool altCam = false;
bool back = false;
bool automatic = true;
bool walk = false;

//Random Variables
Camera belzCamera;
Camera camera;
Projection projection;
Viewport viewport;
Vector3 mouse;
Object cameraObject;
Object object;
Object person;
Vector3 points[100];

//Textures
GLuint head[6];
GLuint body[6];
GLuint leg[6];
GLuint arm[6];

//Character parts
Group character;

//Controller
MatrixTransform control;

//Head
Cube headCube;
MatrixTransform headTranslation;
MatrixTransform headRotation;
MatrixTransform headScaling;

//Body
Cube bodyCube;
MatrixTransform bodyTranslation;
MatrixTransform bodyRotation;
MatrixTransform bodyScaling;

//Arms
Cube armCube;
MatrixTransform leftArmTranslation;
MatrixTransform rightArmTranslation;
MatrixTransform leftArmRotation;
MatrixTransform rightArmRotation;
MatrixTransform leftArmScaling;
MatrixTransform rightArmScaling;

//Legs
Cube legCube;
MatrixTransform leftLegTranslation;
MatrixTransform rightLegTranslation;
MatrixTransform leftLegRotation;
MatrixTransform rightLegRotation;
MatrixTransform leftLegScaling;
MatrixTransform rightLegScaling;


//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	Matrix4 transform;
	Matrix4 temp;
	Matrix4 reverseTemp;
	temp = leftArmRotation.get();
	reverseTemp = temp;
	if (walk) {
		if (forw) {
			temp.makeRotateX(degree);
			reverseTemp.makeRotateX(-degree);
			degree++;
			if (degree == 20)
				forw = !forw;
		}
		else {
			temp.makeRotateX(degree);
			reverseTemp.makeRotateX(-degree);
			std::cout << "ASD" << std::endl;
			degree--;
			if (degree == -20)
				forw = !forw;
		}
	}
	else {
		degree = 0;
		temp.identity();
		reverseTemp.identity();
	}
	transform.makeTranslate(0, -1.5, 0);
	temp = temp * transform;
	reverseTemp = reverseTemp * transform;
	transform.makeTranslate(0, 1.5, 0);
	temp = transform * temp;
	reverseTemp = transform * reverseTemp;
	leftArmRotation.set(temp);
	rightLegRotation.set(temp);
	rightArmRotation.set(reverseTemp);
	leftLegRotation.set(reverseTemp);
  displayCallback();         // call display routine to show the object
}

void Window::load() {
	// Generate light source:
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	camera.set(e, d, up);
	object.move(0, 1, 0);
	cameraObject.set(initial.get(0),initial.get(1),initial.get(2));
	bCurve.setPoints(initial, Vector4(-2, 8, -4, 0), Vector4(2, 8, 4, 0), endV);
	for (int i = 0; i < 100; i++) {
		points[i] = bCurve.evalBCurve((double)i / 100);
	}
	belzCamera.set(points[0], belzD, belzUp);
	loadTextures();
	loadCharacter();
}
//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  viewport.set(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  projection.set(60.0, double(width) / double(height), 1.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glColor3f(0, 0, 1);
	//Setting moving camera
	Matrix4 glmatrix;
	if (cam) {
		if (t == 99) {
			back = true;
		}
		if (t == 0)
			back = false;
		Vector3 upd = belzCamera.upd;
		belzCamera.set(points[t], Vector3(0,0,0), upd);
		std::cout << t << std::endl;
	}
	if (altCam) {
		glmatrix = belzCamera.getInverse();
	}
	else {
		glmatrix = camera.getInverse();
	}
	//Drawing Light Source

	Matrix4 temp;
	temp.makeTranslate(position[0], position[1], position[2]);
	setMatrix(glmatrix, temp);
	glColor3f(1, 1, 0);
	glutSolidSphere(.5, 100, 100);

	//Seting main objects
	glColor3d(1, 0, 0);
	setMatrix(glmatrix, object.getMatrix());
	glutSolidCube(2);
	temp.makeTranslate(3, 1.5, 0);
	setMatrix(glmatrix, temp);
	glColor3d(1, 0, 1);
	glutSolidCube(3); 
	temp.makeTranslate(0, 1.5, 3);
	setMatrix(glmatrix, temp);
	glColor3d(0, 1, 1);
	glutSolidCube(3);
	temp.makeTranslate(0, 1.5, -3);
	setMatrix(glmatrix, temp);
	glColor3d(1, 1, 0);
	glutSolidCube(3);
	temp.makeTranslate(-3, 1.5, 0);
	setMatrix(glmatrix, temp);
	glColor3d(1, 1, 1);
	glutSolidCube(3);

	//Setting Floor
	setMatrix(glmatrix);
	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glColor3d(0.5, 0.6, 0.7);
	glVertex3d(-10, 0, -10);
	glVertex3d(-10, 0, 10);
	glVertex3d(10, 0, 10);
	glVertex3d(10, 0, -10);
	glEnd();

	//Drawing Bezier Curve
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 99; i++) {
		Vector3 current = points[i];
		Vector3 next = points[i + 1];
		glLineWidth(2.5);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3d(current.getX(), current.getY(), current.getZ());
		glVertex3d(next.getX(), next.getY(), next.getZ());
	}
	glEnd();

	//Drawing Head
	temp = glmatrix;
	control.set(person.getMatrix());
	character.draw(temp);
	


	//Drawing Camera
	setMatrix(glmatrix, cameraObject.getMatrix());
	glColor3f(0, 1, 1);
	glutSolidSphere(.5,100,100);
	if (cam) {
		Vector3 current;
		current = points[t];
		cameraObject.set(current.getX(), current.getY(), current.getZ());
		if (automatic) {
			if (!back) {
				t++;
			}
			else {
				t--;
			}
		}
	}
	glFlush();
	glutSwapBuffers();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when users press specific keys on the keyboard
void Window::keyboardCallback(unsigned char key, int xn, int yn) {
	glMatrixMode(GL_PROJECTION);
	Matrix4 temp;
	switch (key) {
	case'q':
		person.rotateY(5);
		temp.makeRotateY(5);
		ahead = temp * ahead;
		side = temp * side;
		camera.rotateDirectionY(5);
		break;
	case'e':
		person.rotateY(-5);
		temp.makeRotateY(-5);
		ahead = temp * ahead;
		side = temp * side;
		camera.rotateDirectionY(-5);
		break;
	case 'z':
		camera.moveUp(1);
		break;
	case 'Z':
		camera.moveDown(1);
		break;
	case 'w':
		walk = true;
		person.move(ahead.get(0), ahead.get(1), ahead.get(2));
		camera.move(Vector3(ahead.get(0),ahead.get(1),ahead.get(2)),1);
		break;
	case's':
		walk = true;
		person.move(-ahead.get(0), -ahead.get(1), -ahead.get(2));
		camera.move(Vector3(-ahead.get(0), -ahead.get(1), -ahead.get(2)), 1);
		break;
	case 'a':
		person.move(side.get(0), side.get(1), side.get(2));
		camera.move(Vector3(side.get(0), side.get(1), side.get(2)), 1);
		break;
	case 'd':
		person.move(-side.get(0), -side.get(1), -side.get(2));
		camera.move(Vector3(-side.get(0), -side.get(1), -side.get(2)), 1);
		break;
	case 'i':
		camera.moveForward(1);
		break;
	case'k':
		camera.moveBackward(1);
		break;
	case 'j':
		camera.moveLeft(1);
		break;
	case 'l':
		camera.moveRight(1);
		break;
	case 'r':
		t = 0;
		cameraObject.set(initial.get(0), initial.get(1), initial.get(2));
		object.reset();
		object.move(0, 1, 0);
		belzCamera.set(points[0], belzD, belzUp);
		person.reset();
		camera.set(e, d, up);
		ahead = Vector4(0, 0, -1, 0);
		side = Vector4(-1, 0, 0, 0);
		break;
	case 'p':
		cam = !cam;
		break;
	case'o':
		altCam = !altCam;
		break;
	case'+':
		t++;
		if (t == 100)
			t = 99;
		break;
	case'-':
		t--;
		if (t == 0)
			t = 1;
		break;
	case'.':
		automatic = !automatic;
		break;
	}
	glMatrixMode(GL_MODELVIEW);

}

void Window::keyboardRelease(unsigned char key, int xn, int yn) {
	switch (key) {
	case 'w':
		walk = false;
		break;
	case's':
		walk = false;
		break;
	}

}
void Window::funcMouseCallback(int button, int state, int x, int y) {
	double tempX = (2.0*x - Window::width) / Window::width;
	double tempY = (Window::height - 2.0*y) / Window::height;
	mouse.set(tempX, tempY, 0);
	double d = mouse.length();
	d = (d < 1.0) ? d : 1.0;
	mouse.set(tempX, tempY, sqrtf(1.001 - d*d));
	mouse.normalize();
}

void Window::funcMouseMovement(int x, int y) {
	Vector3 newPosition;
	Matrix4 temp;
	double tempX = (2.0*x - Window::width) / Window::width;
	double tempY = (Window::height - 2.0*y) / Window::height;
	newPosition.set(tempX, tempY, 0);
	double d = newPosition.length();
	d = (d < 1.0) ? d : 1.0;
	newPosition.set(tempX, tempY, sqrtf(1.001 - d*d));
	newPosition.normalize();
	mouse.normalize();
	Vector3 direction = newPosition - mouse;
	//if (x == 0 || y == 0 || x == width || y == height)
		//glutWarpPointer(Window::width / 2, Window::height / 2);
	double speed = direction.length();
	if (speed > 0.001) {
		Vector3 axis = axis.cross(mouse, newPosition);
		//Globals::object.spinV(speed * 100, axis);
		camera.rotate(axis, speed * 10);
		mouse.set(newPosition.getX(), newPosition.getY(), newPosition.getZ());
	}
}

void Window::funcKeyboardCallback(int key, int xn, int yn) {
	glMatrixMode(GL_PROJECTION);
	switch (key) {
	case GLUT_KEY_UP:
		object.move(0, 1, 0);
		break;
	case GLUT_KEY_DOWN:
		object.move(0, -1, 0);
		break;
	case GLUT_KEY_LEFT:
		object.move(1, 0, 0);
		break;
	case GLUT_KEY_RIGHT:
		object.move(-1, 0, 0);
		break;
	}
	glMatrixMode(GL_MODELVIEW);
}

void Window::setMatrix(Matrix4 camera, Matrix4 world) {
	glMatrixMode(GL_MODELVIEW);  
	Matrix4 temp;
	temp = camera * world;
	temp.transpose();
	glLoadMatrixd(temp.getPointer());
}

void Window::setMatrix(Matrix4 camera) {
	glMatrixMode(GL_MODELVIEW);
	Matrix4 temp = camera;
	temp.transpose();
	glLoadMatrixd(temp.getPointer());
}



void Window::loadCharacter() {
	Matrix4 temp;
	Matrix4 id;
	id.identity();

	//Setting up Controller
	temp.makeTranslate(0, 0, 10);
	control = MatrixTransform(temp);

	//Setting up Head
	headCube = Cube(2);
	headCube.setTexture(head);
	headRotation = MatrixTransform(id);
	headScaling = MatrixTransform(id);
	temp.makeTranslate(0, 7, 0);
	headTranslation = MatrixTransform(temp);
	headRotation.addChild(&headCube);
	headScaling.addChild(&headRotation);
	headTranslation.addChild(&headScaling);
	control.addChild(&headTranslation);

	//Setting up body
	bodyCube = Cube(1);
	bodyCube.setTexture(body);
	bodyRotation = MatrixTransform(id);
	temp.makeScale(2, 3, 1);
	bodyScaling = MatrixTransform(temp);
	temp.makeTranslate(0, 4.5, 0);
	bodyTranslation = MatrixTransform(temp);
	bodyRotation.addChild(&bodyCube);
	bodyScaling.addChild(&bodyRotation);
	bodyTranslation.addChild(&bodyScaling);
	control.addChild(&bodyTranslation);

	//Setting up Arms
	armCube = Cube(1);
	armCube.setTexture(arm);
	leftArmRotation = MatrixTransform(id);
	rightArmRotation = MatrixTransform(id);
	temp.makeScale(1, 3, 1);
	leftArmScaling = MatrixTransform(temp);
	rightArmScaling = MatrixTransform(temp);
	temp.makeTranslate(1.5, 4.5, 0);
	leftArmTranslation = MatrixTransform(temp);
	temp.makeTranslate(-(1.5), 4.5, 0);
	rightArmTranslation = MatrixTransform(temp);
	leftArmScaling.addChild(&armCube);
	rightArmScaling.addChild(&armCube);
	leftArmRotation.addChild(&leftArmScaling);
	rightArmRotation.addChild(&rightArmScaling);
	leftArmTranslation.addChild(&leftArmRotation);
	rightArmTranslation.addChild(&rightArmRotation);
	control.addChild(&leftArmTranslation);
	control.addChild(&rightArmTranslation);

	//Setting up Legs
	legCube = Cube(1);
	legCube.setTexture(leg);
	leftLegRotation = MatrixTransform(id);
	rightLegRotation = MatrixTransform(id);
	temp.makeScale(1, 3, 1);
	leftLegScaling = MatrixTransform(temp);
	rightLegScaling = MatrixTransform(temp);
	temp.makeTranslate(.5, 1.5, 0);
	leftLegTranslation = MatrixTransform(temp);
	temp.makeTranslate(-.5, 1.5, 0);
	rightLegTranslation = MatrixTransform(temp);
	leftLegScaling.addChild(&legCube);
	rightLegScaling.addChild(&legCube);
	leftLegRotation.addChild(&leftLegScaling);
	rightLegRotation.addChild(&rightLegScaling);
	leftLegTranslation.addChild(&leftLegRotation);
	rightLegTranslation.addChild(&rightLegRotation);
	control.addChild(&leftLegTranslation);
	control.addChild(&rightLegTranslation);

	character.addChild(&control);

}

void Window::loadTextures() {

	//Loading Head Texture
	head[0] = SOIL_load_OGL_texture
		(
		"headfront.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	head[1] = SOIL_load_OGL_texture
		(
		"headleft.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	head[2] = SOIL_load_OGL_texture
		(
		"headback.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	head[3] = SOIL_load_OGL_texture
		(
		"headright.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	head[4] = SOIL_load_OGL_texture
		(
		"headtop.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	head[5] = SOIL_load_OGL_texture
		(
		"headbottom.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);


	//Loading Body Textures

	body[0] = SOIL_load_OGL_texture
		(
		"bodyfront.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	body[1] = SOIL_load_OGL_texture
		(
		"bodyleft.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	body[2] = SOIL_load_OGL_texture
		(
		"bodyback.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	body[3] = SOIL_load_OGL_texture
		(
		"bodyright.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	body[4] = SOIL_load_OGL_texture
		(
		"bodytop.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	body[5] = SOIL_load_OGL_texture
		(
		"bodybottom.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	//Loading Arm Textures

	arm[0] = SOIL_load_OGL_texture
		(
		"armfront.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	arm[1] = SOIL_load_OGL_texture
		(
		"armleft.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	arm[2] = SOIL_load_OGL_texture
		(
		"armback.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	arm[3] = SOIL_load_OGL_texture
		(
		"armright.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	arm[4] = SOIL_load_OGL_texture
		(
		"armtop.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	arm[5] = SOIL_load_OGL_texture
		(
		"armbottom.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	//Loading Leg Textures

	leg[0] = SOIL_load_OGL_texture
		(
		"legfront.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	leg[1] = SOIL_load_OGL_texture
		(
		"legleft.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	leg[2] = SOIL_load_OGL_texture
		(
		"legback.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	leg[3] = SOIL_load_OGL_texture
		(
		"legright.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	leg[4] = SOIL_load_OGL_texture
		(
		"legtop.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	leg[5] = SOIL_load_OGL_texture
		(
		"legbottom.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
}