#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include"Kruskal.h"

Kruskal myMaze = Kruskal(8);
int **Map;
int xPlayer,yPlayer;
int inDoor,outDoor,xNim,yNim;

void placeDoor() {
  xNim = (rand() % myMaze.getLength())*2+1;
  yNim = (rand() % myMaze.getLength())*2+1;
  inDoor = myMaze.getDorPos();
  outDoor = myMaze.getDorPos();
  Map[0][inDoor] = 0;
  Map[myMaze.getLength()*2][outDoor] = 0;
}

void settingUp(int size){
  myMaze = Kruskal(size);
  myMaze.doGenerate();
  Map = myMaze.getMap();
  placeDoor();
  xPlayer=outDoor;
  yPlayer=myMaze.getLength()*2;
}

void drawBox(char color,float arg1, float arg2, float arg3, float arg4) {
  if (color=='R') {
    glColor3f(1,0,0);
  }else if (color=='G') {
    glColor3f(0,1,0);
  }else{
    glColor3f(0,0,1);
  }
  glBegin(GL_POLYGON);
    glVertex3f (arg1,arg2,0.0);
    glVertex3f (arg3,arg2,0.0);
    glVertex3f (arg3,arg4,0.0);
    glVertex3f (arg1,arg4,0.0);
  glEnd();
}

void drawNim() {
  //one
  drawBox('R',0.1+xNim,0.1+yNim,0.18+xNim,0.9+yNim);

  //o
  drawBox('R',0.21+xNim,0.1+yNim,0.3+xNim,0.9+yNim);
  drawBox('R',0.3+xNim,0.1+yNim,0.45+xNim,0.19+yNim);
  drawBox('R',0.45+xNim,0.1+yNim,0.54+xNim,0.9+yNim);
  drawBox('R',0.3+xNim,0.81+yNim,0.45+xNim,0.9+yNim);

  //eight
  drawBox('R',0.57+xNim,0.1+yNim,0.66+xNim,0.9+yNim);
  drawBox('R',0.57+xNim,0.1+yNim,0.82+xNim,0.19+yNim);
  drawBox('R',0.82+xNim,0.1+yNim,0.91+xNim,0.9+yNim);
  drawBox('R',0.66+xNim,0.81+yNim,0.91+xNim,0.9+yNim);
  drawBox('R',0.66+xNim,0.46+yNim,0.91+xNim,0.55+yNim);
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT);
  for (int i = 0; i < 17; i++){
    for (int j = 0; j < 17; j++){
      if (Map[i][j]==1){
        drawBox('B',j,i,j+1,i+1);
      }
    }
  }
  drawBox('G',xPlayer,yPlayer,xPlayer+1,yPlayer+1);
  drawNim();
	glFlush();
}

void input(unsigned char key, int x, int y)
{
    if (key=='c' || key=='C'){
      settingUp(8);
    }
    if((key=='w' || key=='W') && yPlayer < 16 && Map[yPlayer+1][xPlayer] != 1){
      yPlayer+=1;
    }
    if((key=='a' || key=='A') && Map[yPlayer][xPlayer-1] != 1){
      xPlayer-=1;
    }
    if((key=='s' || key=='S') && yPlayer > 0 && Map[yPlayer-1][xPlayer] != 1){
      yPlayer-=1;
    }
    if((key=='d' || key=='D') && Map[yPlayer][xPlayer+1] != 1){
      xPlayer+=1;
    }
    display();
}

void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.5,18.5,-1.5,18.5);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,1.0);
}

int main(int argc, char* argv[]){
  srand(time(NULL));
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	//glutInitWindowPosition(100,100);
	glutCreateWindow("Maze Kruskal Algorithm");
	glutDisplayFunc(display);
  glutKeyboardFunc(input);
  settingUp(8);
	myinit();
	glutMainLoop();

	return 0;
}
