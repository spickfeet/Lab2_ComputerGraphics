#include <stdlib.h>
#include <glut.h>

static GLfloat spin = 0.0;
bool spinStarter; // Флаг для вращения
bool isMousePressed; // флаг нажатой мыши
int mouseX = 5, mouseY = 5; // координаты мыши
double size = 40; // Размер желтого квадрата

void spinDisplay(void) // Метод вращения 
{
	if (spinStarter == false) return;
	spin = spin + 0.1;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y) 
{ 
	if (button == GLUT_LEFT_BUTTON) spinStarter = true; // запустить вращение
	if (button == GLUT_RIGHT_BUTTON) spinStarter = false; // остановить вращение
}
void mouseMotion(int x, int y) // получаем координаты курсора и приводим всё в одну систему координат
{
	if (mouseX - size / 2 < x - 400 && mouseX + size / 2 > x - 400 && mouseY - size / 2 < 400 - y && mouseY + size / 2 > 400 - y)
	{
		mouseX = x - 400;
		mouseY = 400 - y;
		glutPostRedisplay();
	}
}
void keyboard(unsigned char key, int x, int y) {
	if (key == 'x')
		spinStarter = true; // запустить вращение
	if (key == 'X')
		spinStarter = false; // остановить вращение
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
	
	// Отрисовать желтый квадрат относительно координат мыши
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
	glutCreateWindow("Квадраты");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutIdleFunc(spinDisplay);
	glutMainLoop();
	return 0;
}
