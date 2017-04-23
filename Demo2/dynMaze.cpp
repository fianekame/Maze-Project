#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <time.h>
//[y][x]
bool cek = true;
int xPlayer=7,yPlayer=16;
int xk,yk,kunci;
int hitung; //8x8-1
int wall = 1;
int road = 0;
int mazeFormat [17][17];

void Player(){
  glBegin(GL_POLYGON);
  //x,y
  glColor3f(1,0,0);
    glVertex3f (xPlayer,yPlayer,0.0);
    glVertex3f (xPlayer+1,yPlayer, 0.0);
    glVertex3f (xPlayer+1,yPlayer+1, 0.0);
    glVertex3f (xPlayer,yPlayer+1, 0.0);
  glEnd();
}


void rubah(){
    for (int i = 0; i < 17; i++) {
      for (int j = 0; j < 17; j++) {
        if (mazeFormat[i][j] == kunci) {
          mazeFormat[i][j] = mazeFormat[xk][yk];
        }
      }
    }
}

void jebol() {
  int arah = (rand() % 4);
  switch (arah) {
    case 0:
      if (xk+2 <= 15) {
        if (mazeFormat[xk+2][yk] != mazeFormat[xk][yk]) {
          mazeFormat[xk+1][yk] = road;
          kunci = mazeFormat[xk+2][yk];
          rubah();
          hitung--;
        }
      }
      else{
        jebol();
      }
      break;
    case 1:
      if (yk+2 <= 15) {
        if (mazeFormat[xk][yk+2] != mazeFormat[xk][yk]) {
          mazeFormat[xk][yk+1] = road;
          kunci = mazeFormat[xk][yk+2];
          rubah();
          hitung--;
        }
      }
      else{
        jebol();
      }
      break;
      case 2:
        if (xk-2 >= 0) {
          if (mazeFormat[xk-2][yk] != mazeFormat[xk][yk]) {
            mazeFormat[xk-1][yk] = road;
            kunci = mazeFormat[xk-2][yk];
            rubah();
            hitung--;
          }
        }
        else{
          jebol();
        }
        break;
        case 3:
          if (yk-2 >= 0) {
            if (mazeFormat[xk][yk-2] != mazeFormat[xk][yk]) {
              mazeFormat[xk][yk-1] = road;
              kunci = mazeFormat[xk][yk-2];
              rubah();
              hitung--;
            }
          }
          else{
            jebol();
          }
          break;
  }

}

void generateMaze(){
  hitung = 63;
  int rdl = 2;
  for (int i = 0; i < 17; i++) {
    for (int j = 0; j < 17; j++) {
      if (i % 2 == 0 || j % 2 == 0) {
        mazeFormat[i][j] = wall;
      }
      else{
        mazeFormat[i][j] = rdl;
        rdl++;
      }
    }
  }
  while (hitung != 0) {
    int xkor = (rand() % 8+1)*2-1;
    int ykor = (rand() % 8+1)*2-1;
    xk = xkor;
    yk = ykor;
    jebol();
    //melakukan ngacak kodinat
  }
}

void drawMaze(){
  for (int i = 0; i < 17; i++) {
    for (int j = 0; j < 17; j++) {
      if (mazeFormat[i][j]==1) {
        glBegin(GL_POLYGON);
        //x,y
          glColor3f(0,0,1);
          glVertex3f (j,i,0.0);
          glVertex3f (j+1,i, 0.0);
          glVertex3f (j+1,i+1, 0.0);
          glVertex3f (j,i+1, 0.0);
        glEnd();
      }
    }
  }
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4);
  drawMaze();
  Player();
	glFlush();
}


void input(unsigned char key, int x, int y) {
  if (key=='c' || key=='C') {
    generateMaze();
    xPlayer=7;
    yPlayer=16;
  }
  if (key=='s' || key=='S') {
    yPlayer-=1;
  }
  if (key=='a' || key=='A') {
    xPlayer-=1;
  }
  if (key=='d' || key=='D') {
    xPlayer+=1;
  }
  if (key=='w' || key=='W') {
    yPlayer+=1;
  }
  display();
}

void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0,19.0,-2.0,19.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,1.0);
}

int main(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	//glutInitWindowPosition(100,100);
	glutCreateWindow("DINAMIS MAZE DEMO");
	glutDisplayFunc(display);
  glutKeyboardFunc(input);
	myinit();
  generateMaze();
	glutMainLoop();
	return 0;
}
