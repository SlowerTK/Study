#include <GL/glut.h>
#include <math.h>

const int slices = 50;
const int stacks = 50;
const float innerRadius = 0.5;
const float outerRadius = 1.0;
bool showWireframe = true;
bool showInside = false;
float angle = 0.0f;

void drawWireframeTorus() {
	for(int i = 0; i < slices; ++i) {
		float theta1 = 2.0f * 3.1415926f * float(i) / float(slices);
		float theta2 = 2.0f * 3.1415926f * float(i + 1) / float(slices);

		glBegin(GL_QUAD_STRIP);
		for(int j = 0; j <= stacks; ++j) {
			float phi = 2.0f * 3.1415926f * float(j) / float(stacks);
			float x = (outerRadius + innerRadius * cos(phi)) * cos(theta2);
			float y = (outerRadius + innerRadius * cos(phi)) * sin(theta2);
			float z = innerRadius * sin(phi);
			glVertex3f(x, y, z);

			x = (outerRadius + innerRadius * cos(phi)) * cos(theta1);
			y = (outerRadius + innerRadius * cos(phi)) * sin(theta1);
			z = innerRadius * sin(phi);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void collorPick(float x1, float x2, float y1, float y2, float z1, float z2) {
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); // Красный
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	if(showInside) {
		glColor3f(0.0f, 1.0f, 0.0f); // Зеленый
		glVertex3f(x1, y1, z1);
		glVertex3f(x1, y1, -z1);

		//glColor3f(0.0f, 0.0f, 1.0f); // Синий
		//glVertex3f(x2, y2, z2);
		//glVertex3f(x2, y2, -z2);
	}
	glEnd();
}

void drawSolidTorus() {
	for(int i = 0; i < slices; ++i) {
		float theta1 = 2.0f * 3.1415926f * float(i) / float(slices);
		float theta2 = 2.0f * 3.1415926f * float(i + 1) / float(slices);

		for(int j = 0; j <= stacks; ++j) {
			float phi = 2.0f * 3.1415926f * float(j) / float(stacks);
			float x1 = (outerRadius + innerRadius * cos(phi)) * cos(theta1);
			float y1 = (outerRadius + innerRadius * cos(phi)) * sin(theta1);
			float z1 = innerRadius * sin(phi);
			float x2 = (outerRadius + innerRadius * cos(phi)) * cos(theta2);
			float y2 = (outerRadius + innerRadius * cos(phi)) * sin(theta2);
			float z2 = innerRadius * sin(phi);

			collorPick(x1, x2, y1, y2, z1, z2);
		}
	}
}

void drawTorus() {
	if(showWireframe)
		drawWireframeTorus();
	else
		drawSolidTorus();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glRotatef(angle, 1.0f, 1.0f, 0.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	drawTorus();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void update(int value) {
	angle += 0.5f;
	if(angle > 360) {
		angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
	if(key == ' ') {
		showWireframe = !showWireframe;
		glutPostRedisplay();
	}
	if(key == 'v') {
		showInside = !showInside;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Wireframe Torus");

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(16, update, 0);

	glutMainLoop();

	return 0;
}