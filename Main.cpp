#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include"Kruskal.h"

Kruskal myMaze = Kruskal(8);
int **Map,mazeSize=8;
int xPlayer,yPlayer,playerType=0;
int inDoor,outDoor;
bool is3D;

void settingUp(int size){
  myMaze = Kruskal(size);
  myMaze.doGenerate();
  Map = myMaze.getMap();
  xNim = (rand() % myMaze.getLength())*2+1;
  yNim = (rand() % myMaze.getLength())*2+1;
  placeDoor();
  xPlayer=outDoor;
  yPlayer=myMaze.getLength()*2;
}

void drawBox(float colR,float colG,float colB,float zPlus,float zMin,float arg1, float arg2, float arg3, float arg4, float alpha) {
  //depan
  //x1 1 y1 2 x2 3
  glColor4f(colR,colG,1,alpha);
  glBegin(GL_POLYGON);
    glVertex3f (arg1,arg2,zPlus);
    glVertex3f (arg3,arg2,zPlus);
    glVertex3f (arg3,arg4,zPlus);
    glVertex3f (arg1,arg4,zPlus);
  glEnd();
  //belakang
  glColor4f(colR,1,colB,alpha);
  glBegin(GL_POLYGON);
    glVertex3f (arg1,arg2,zMin);
    glVertex3f (arg3,arg2,zMin);
    glVertex3f (arg3,arg4,zMin);
    glVertex3f (arg1,arg4,zMin);
  glEnd();
  //kiri
  glColor4f(1,colG,colB,alpha);
  glBegin(GL_POLYGON);
    glVertex3f (arg1,arg2,zPlus);
    glVertex3f (arg1,arg4,zPlus);
    glVertex3f (arg1,arg4,zMin);
    glVertex3f (arg1,arg2,zMin);
  glEnd();
  //kanan
  glColor4f(1,colR,1,alpha);
  glBegin(GL_POLYGON);
    glVertex3f (arg3,arg2,zPlus);
    glVertex3f (arg3,arg2,zMin);
    glVertex3f (arg3,arg4,zMin);
    glVertex3f (arg3,arg4,zPlus);
  glEnd();
  //bawah
  glColor4f(0.5,0.5,colB,alpha);
  glBegin(GL_POLYGON);
    glVertex3f (arg1,arg2,zPlus);
    glVertex3f (arg1,arg2,zMin);
    glVertex3f (arg3,arg2,zMin);
    glVertex3f (arg3,arg2,zPlus);
  glEnd();
  //atas
  glColor4f(colR,0.8,0.8,alpha);
  glBegin(GL_POLYGON);
    glVertex3f (arg1,arg4,zPlus);
    glVertex3f (arg3,arg4,zPlus);
    glVertex3f (arg3,arg4,zMin);
    glVertex3f (arg1,arg4,zMin);
  glEnd();
}
void drawNim() {
  //num one
  drawBox(0.1,-0.1,0.1+xNim,0.1+yNim,0.18+xNim,0.9+yNim,1,0,0.4,1);
  //num zero
  drawBox(0.1,-0.1,0.21+xNim,0.1+yNim,0.3+xNim,0.9+yNim,1,0,0.4,1);
  drawBox(0.1,-0.1,0.3+xNim,0.1+yNim,0.45+xNim,0.19+yNim,1,0,0.4,1);
  drawBox(0.1,-0.1,0.45+xNim,0.1+yNim,0.54+xNim,0.9+yNim,1,0,0.4,1);
  drawBox(0.1,-0.1,0.3+xNim,0.81+yNim,0.45+xNim,0.9+yNim,1,0,0.4,1);
  //num eight
  drawBox(0.1,-0.1,0.57+xNim,0.1+yNim,0.66+xNim,0.9+yNim,1,0,0.4,1);
  drawBox(0.1,-0.1,0.57+xNim,0.1+yNim,0.82+xNim,0.19+yNim,1,0,0.4,1);
  drawBox(0.1,-0.1,0.82+xNim,0.1+yNim,0.91+xNim,0.9+yNim,1,0,0.4,1);
  drawBox(0.1,-0.1,0.66+xNim,0.81+yNim,0.91+xNim,0.9+yNim,1,0,0.4,1);
  drawBox(0.1,-0.1,0.66+xNim,0.46+yNim,0.91+xNim,0.55+yNim,1,0,0.4,1);
}
void display(){
  setDisplay();
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  for (int i = 0; i < myMaze.getSize(); i++){
    for (int j = 0; j < myMaze.getSize(); j++){
      if (Map[i][j]==1){
        drawBox(0.5,-0.5,j,i,j+1,i+1,0.1,0.1,0.1,1);
      }
    }
  }
  setNim();
  //player
  drawPlayer();
  //floor
  drawBox(-0.51,-0.61,0,0,mazeSize*2+1,mazeSize*2+1,0.7,0.7,0.7,0.2);
  glPopMatrix();
  glutSwapBuffers();
}

void nimRot() {
  if(rotBy == 0){xNimRot += 0.1;}
  if(rotBy == 1){yNimRot += 0.1;}
  if(rotBy == 2){zNimRot += 0.1;}
  glutPostRedisplay();
}

void input(unsigned char key, int x, int y)
{
    if (key=='c' || key=='C'){
      settingUp(mazeSize);
    }
    if (key=='5' || key=='6' || key=='7' || key=='8' || key=='9' || key=='0'){
      if (key=='0') {
        mazeSize=10;
      }
      else{
        mazeSize = key - '0';
      }
      settingUp(mazeSize);
      setOrtho(mazeSize);
    }
    if(key=='v' || key=='V'){
        if(is3D==false){
            is3D = true;
        }else{
            is3D = false;

    if(key=='p' || key=='P'){
      if (playerType==0) {
        playerType=1;
      }else{
        playerType=0;
      }
    }
    if((key=='w' || key=='W') && yPlayer < myMaze.getLength()*2 && Map[yPlayer+1][xPlayer] != 1){
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

void mouse(int button, int state, int x, int y){
    //available soon
}

void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  //3Ddependeci
  glOrtho(-10.5, 10.5, -10.5, 10.5, -12.5, 12.5);
  glMatrixMode(GL_MODELVIEW);
  //3Ddependeci
  glShadeModel(GL_FLAT);
	glClearColor(1.0,1.0,1.0,1.0);
  //tranparanceDependeci
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
}

int main(int argc, char* argv[]){
  srand(time(NULL));
  settingUp(8);
	glutInit(&argc,argv);
  //depth is 3Ddependeci
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("Maze || Kruskal Algorithm");
  myinit();
	glutDisplayFunc(display);
  glutKeyboardFunc(input);
  glutMouseFunc(mouse);
	glutMainLoop();

	return 0;
}
