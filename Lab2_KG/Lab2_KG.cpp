#include <stdlib.h>
#include <glut.h>

static GLfloat spin = 0.0;
bool spinStarter;
bool isMousePressed;
int mouseX = 5, mouseY = 5;
double size = 50;

void spinDisplay(void)
{
	if (spinStarter == false) return;
	spin = spin + 0.02;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) spinStarter = true;
	if (button == GLUT_RIGHT_BUTTON) spinStarter = false;
}
void mouseMotion(int x, int y) {
	if (mouseX - size / 2 < x - 400 && mouseX + size / 2 > x - 400 && mouseY - size / 2 < 400 - y && mouseY + size / 2 > 400 - y)
	{
		mouseX = x - 400;
		mouseY = 400 - y;
	}
}
void keyboard(unsigned char key, int x, int y) {
	if (key == 'x')
		spinStarter = true;
	if (key == 'X')
		spinStarter = false;
	if (key == 27)
		exit(0);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-15.0, -15.0);
	glVertex2f(15.0, -15.0);
	glVertex2f(15.0, 15.0);
	glVertex2f(-15.0, 15.0);
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0);
	glVertex2f(mouseX - size / 2, mouseY + size / 2);
	glVertex2f(mouseX - size / 2, mouseY - size / 2);
	glVertex2f(mouseX + size / 2, mouseY - size / 2);
	glVertex2f(mouseX + size / 2, mouseY + size / 2);
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-400, 400, -400, 400, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutIdleFunc(spinDisplay);
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}
