
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4);
  glBegin(GL_POLYGON);
  glColor3f(0,1,0);
    glVertex3f (0.1,0.1,0.0);
    glVertex3f (0.18,0.1, 0.0);
    glVertex3f (0.18,0.9, 0.0);
    glVertex3f (0.1,0.9, 0.0);
  glEnd();

  glBegin(GL_POLYGON);
  glColor3f(0,1,0);
    glVertex3f (0.21,0.1,0.0);
    glVertex3f (0.3,0.1, 0.0);
    glVertex3f (0.3,0.9, 0.0);
    glVertex3f (0.21,0.9, 0.0);
  glEnd();

	glBegin(GL_POLYGON);
  glColor3f(0,1,0);
    glVertex3f (0.3,0.1,0.0);
    glVertex3f (0.45,0.1, 0.0);
    glVertex3f (0.45,0.19, 0.0);
    glVertex3f (0.3,0.19, 0.0);
  glEnd();

	glBegin(GL_POLYGON);
  glColor3f(0,1,0);
    glVertex3f (0.45,0.1,0.0);
    glVertex3f (0.54,0.1, 0.0);
    glVertex3f (0.54,0.9, 0.0);
    glVertex3f (0.45,0.9, 0.0);
  glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0,1,0);
		glVertex3f (0.3,0.81,0.0);
		glVertex3f (0.45,0.81, 0.0);
		glVertex3f (0.45,0.9, 0.0);
		glVertex3f (0.3,0.9, 0.0);
	glEnd();


	//dekapan

	glBegin(GL_POLYGON);
	glColor3f(1,1,0);
		glVertex3f (0.57,0.1,0.0);
		glVertex3f (0.66,0.1, 0.0);
		glVertex3f (0.66,0.9, 0.0);
		glVertex3f (0.57,0.9, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f (0.57,0.1,0.0);
		glVertex3f (0.82,0.1, 0.0);
		glVertex3f (0.82,0.19, 0.0);
		glVertex3f (0.57,0.19, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
    glVertex3f (0.82,0.1,0.0);
    glVertex3f (0.91,0.1, 0.0);
    glVertex3f (0.91,0.9, 0.0);
    glVertex3f (0.82,0.9, 0.0);
  glEnd();

	glBegin(GL_POLYGON);
		glVertex3f (0.66,0.81,0.0);
		glVertex3f (0.91,0.81, 0.0);
		glVertex3f (0.91,0.9, 0.0);
		glVertex3f (0.66,0.9, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f (0.66,0.46,0.0);
		glVertex3f (0.91,0.46, 0.0);
		glVertex3f (0.91,0.55, 0.0);
		glVertex3f (0.66,0.55, 0.0);
	glEnd();

	glFlush();
}

void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,1.0,0.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,1.0);
}

int main(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	//glutInitWindowPosition(100,100);
	glutCreateWindow("Coba Nim");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();

	return 0;
}
