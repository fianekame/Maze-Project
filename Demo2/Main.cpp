#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float xPlayer,yPlayer;
int pAtas,pBawah,xnim,ynim,xk,yk;
int temp,walk;
int wall = 1,road = 0;
int map[17][17];

void consoleText(){
  for (int i = 0; i < 17; i++){
    for (int j = 0; j < 17; j++){
      std::cout << map[i][j];
    }std::cout << std::endl;
  }std::cout << std::endl;
}

void changeTemp(){
  for (int i = 0; i < 17; i++){
    for (int j = 0; j < 17; j++){
      if (map[i][j] == temp){
        map[i][j] = map[xk][yk];
      }
    }
  }
}

void destroyer(int xk2, int yk2, int xk1, int yk1){
  map[xk1][yk1] = road;
  temp = map[xk2][yk2];
  changeTemp();
  walk--;
}

void makeWay(){
  //xk+ bwah xk- atas yk+kanan yk-kiri
  int arah = (rand() % 4);
  switch (arah){
    case 0:
      if (xk+2 <= 15){
        if (map[xk+2][yk] != map[xk][yk]){destroyer(xk+2,yk,xk+1,yk);}
      }
      else{
        makeWay();
      }
    break;
    case 1:
      if (xk-2 >= 0){
        if (map[xk-2][yk] != map[xk][yk]){destroyer(xk-2,yk,xk-1,yk);}
      }
      else{
        makeWay();
      }
    break;
    case 2:
      if (yk+2 <= 15){
        if (map[xk][yk+2] != map[xk][yk]){destroyer(xk,yk+2,xk,yk+1);}
      }
      else{
        makeWay();
      }
    break;
    case 3:
      if (yk-2 >= 0){
        if (map[xk][yk-2] != map[xk][yk]){destroyer(xk,yk-2,xk,yk-1);}
      }
      else {
        makeWay();
      }
    break;
  }
}

void placeDoor() {
  pAtas = (rand() % 2+4)*2-1;
  pBawah = (rand() % 2+4)*2-1;
  map[0][pAtas] = road;
  map[16][pBawah] = road;
}

void fillMap(){
  walk = 63;
  int x = 2;
  for (int i = 0; i < 17; i++){
    for (int j = 0; j < 17; j++){
      if (i % 2 == 0 || j % 2 == 0){
        map[i][j] = wall;
      }
      else{
        map[i][j] = x;
        x++;
      }
    }
  }
  consoleText();
  while (walk != 0){
    xk = (rand() % 8+1)*2-1;
    yk = (rand() % 8+1)*2-1;
    makeWay();
  }
  placeDoor();
  xPlayer=pBawah;
  yPlayer=16;
  consoleText();
}

void makeBlock(char color,float arg1, float arg2, float arg3, float arg4) {
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

void Nim() {
  //angka satu
  makeBlock('R',0.1+xnim,0.1+ynim,0.18+xnim,0.9+ynim);

  //angka nol
  makeBlock('R',0.21+xnim,0.1+ynim,0.3+xnim,0.9+ynim);
  makeBlock('R',0.3+xnim,0.1+ynim,0.45+xnim,0.19+ynim);
  makeBlock('R',0.45+xnim,0.1+ynim,0.54+xnim,0.9+ynim);
  makeBlock('R',0.3+xnim,0.81+ynim,0.45+xnim,0.9+ynim);

  //angka delapan
  makeBlock('R',0.57+xnim,0.1+ynim,0.66+xnim,0.9+ynim);
  makeBlock('R',0.57+xnim,0.1+ynim,0.82+xnim,0.19+ynim);
  makeBlock('R',0.82+xnim,0.1+ynim,0.91+xnim,0.9+ynim);
  makeBlock('R',0.66+xnim,0.81+ynim,0.91+xnim,0.9+ynim);
  makeBlock('R',0.66+xnim,0.46+ynim,0.91+xnim,0.55+ynim);
}

void Player(){
  makeBlock('G',xPlayer,yPlayer,xPlayer+1,yPlayer+1);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
  for (int i = 0; i < 17; i++){
    for (int j = 0; j < 17; j++){
      if (map[i][j]==1){
        makeBlock('B',j,i,j+1,i+1);
      }
    }
  }
  Player();
  Nim();
	glFlush();
}

void input(unsigned char key, int x, int y)
{
    if (key=='c' || key=='C'){
      fillMap();
      xnim = (rand() % 8)*2+1;
      ynim = (rand() % 8)*2+1;
    }
    if(key=='w' || key=='W'){
      yPlayer+=0.1;
    }
    if(key=='a' || key=='A'){
      xPlayer-=0.1;
    }
    if(key=='s' || key=='S'){
      yPlayer-=0.1;
    }
    if(key=='d' || key=='D'){
      xPlayer+=0.1;
    }
    display();
}

void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0,18.0,-1.0,18.0);
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
	glutCreateWindow("Maze Demo II | Kruskal Algorithm");
	glutDisplayFunc(display);
  glutKeyboardFunc(input);
  xnim = (rand() % 8)*2+1;
  ynim = (rand() % 8)*2+1;
  fillMap();
	myinit();
	glutMainLoop();

	return 0;
}
