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
int inDoor,outDoor,xNim,yNim,rotBy=1;
float xRot=-20,yRot,xNimRot,yNimRot,zNimRot;
bool is3D;

void placeDoor() {
  inDoor = myMaze.getDorPos();
  outDoor = myMaze.getDorPos();
  Map[0][inDoor] = 0;
  Map[myMaze.getLength()*2][outDoor] = 0;
}
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
void drawBox(float zPlus,float zMin,float left,float down,float right,float top,float colR,float colG,float colB,float colAlpha) {
  glColor4f(colR,colG,colB,colAlpha);
  //depan
  //x1 1 y1 2 x2 3
  glBegin(GL_POLYGON);
    glVertex3f (left,down,zPlus);
    glVertex3f (right,down,zPlus);
    glVertex3f (right,top,zPlus);
    glVertex3f (left,top,zPlus);
  glEnd();
  //belakang
  glBegin(GL_POLYGON);
    glVertex3f (left,down,zMin);
    glVertex3f (right,down,zMin);
    glVertex3f (right,top,zMin);
    glVertex3f (left,top,zMin);
  glEnd();
  glColor4f(colR+0.2,colG+0.2,colB+0.2,colAlpha);
  //kiri
  glBegin(GL_POLYGON);
    glVertex3f (left,down,zPlus);
    glVertex3f (left,top,zPlus);
    glVertex3f (left,top,zMin);
    glVertex3f (left,down,zMin);
  glEnd();
  //kanan
  glBegin(GL_POLYGON);
    glVertex3f (right,down,zPlus);
    glVertex3f (right,down,zMin);
    glVertex3f (right,top,zMin);
    glVertex3f (right,top,zPlus);
  glEnd();
  //bawah
  glBegin(GL_POLYGON);
    glVertex3f (left,down,zPlus);
    glVertex3f (left,down,zMin);
    glVertex3f (right,down,zMin);
    glVertex3f (right,down,zPlus);
  glEnd();
  //atas
  glBegin(GL_POLYGON);
    glVertex3f (left,top,zPlus);
    glVertex3f (right,top,zPlus);
    glVertex3f (right,top,zMin);
    glVertex3f (left,top,zMin);
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
void drawPlayer() {
  glColor4f(0.5,1.0,0.0,1.0);
  glPushMatrix();
  if (playerType==0) {
    glTranslatef(xPlayer+0.5,yPlayer+0.5,0);
    glutSolidCube(1);
  }else{
    glTranslatef(xPlayer+0.5,yPlayer+0.5,-0.5);
    glutSolidCone(0.5,1, 50, 50);
  }
  glPopMatrix();
  //ManualPlayer
  //drawBox(0.5,-0.5,xPlayer,yPlayer,xPlayer+1,yPlayer+1,0,1,1,1);
}
void setOrtho(int size) {
  size = size+2.5;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-size,size,-size,size,-size-2.5,size+2.5);
}
void setNim() {
  glPushMatrix();
  if (is3D==true) {
    glTranslated(0.5+xNim,0.5+yNim,0);
    glRotatef(xNimRot,1,0,0);
    glRotatef(yNimRot,0,1,0);
    glRotatef(zNimRot,0,0,1);
    glScalef(0.8,0.8,1);
    glTranslated(-0.5-xNim,-0.5-yNim,0);
  }
  drawNim();
  glPopMatrix();
}
void setDisplay(){
  glPushMatrix();
  if (is3D==true) {
    glRotatef(yRot,0,1,0);
    glRotatef(xRot,1,0,0);
  }
  glTranslatef(-mazeSize-0.5,-mazeSize-0.5,0);
}
void display(){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  setDisplay();
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
  drawBox(-0.51,-0.61,0,0,mazeSize*2+1,mazeSize*2+1,0.6,0.6,0.6,0.4);
  glPopMatrix();
  glutSwapBuffers();
}
void nimAnimation() {
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
    if(key=='p' || key=='P'){
      if (playerType==0) {
        playerType=1;
      }else{
        playerType=0;
      }
    }
    if(key=='v' || key=='V'){
        if(is3D==false){
            glutIdleFunc(nimAnimation);
            is3D = true;
        }else{
            glutIdleFunc(NULL);
            is3D = false;
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
    if((key=='i' || key=='I' ) && is3D==true){
      xRot-=1;
    }
    if((key=='j' || key=='J' ) && is3D==true){
      yRot-=1;
    }
    if((key=='k' || key=='K' ) && is3D==true){
      xRot+=1;
    }
    if((key=='l' || key=='L' ) && is3D==true){
      yRot+=1;
    }
    display();
}

void mouse(int button, int state, int x, int y){
    switch (button){
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN && is3D==true){rotBy=0;}
        break;
        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_DOWN && is3D==true){rotBy=2;}
        break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN && is3D==true){rotBy=1;}
        break;
        default:
        break;
    }
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
