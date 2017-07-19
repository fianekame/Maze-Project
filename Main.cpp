#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include "Kruskal.h"
#include "Transversal.h"

Kruskal myMaze = Kruskal(8);
Transversal myTran = Transversal();
int **Map,**TransMap,mazeSize=8;
int xPlayer,yPlayer,xEnemy,yEnemy,playerType=0;
int inDoor,outDoor,xNim,yNim,rotBy=1;
float xRot=-20,yRot,xNimRot,yNimRot,zNimRot;
int viewMode = 0;
bool isTrans,isMorning,isEnemyrun=true;
bool diff = false, spec = false, amb = false;
float pos[] = {1,10.5,0};
float ver[] = {0,-1,0};
float alpha = 4.71;
int xRoad,yRoad;

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
        myTran = Transversal(myMaze.getMap(),mazeSize*2+1,size*2-1,size*2-1,inDoor);
        myTran.doTransit();
        TransMap = myTran.getMap();
        pos[1] = size + 2.5;
        size % 2 == 0 ? pos[0] = 1 : pos[0] = 0;
        xPlayer=outDoor; yPlayer=myMaze.getLength()*2;
        xEnemy=size*2-1; yEnemy=size*2-1;
}

void myinit(){
        isMorning == true ? glClearColor(0.5,0.5,1,0.5) : glClearColor(0.0,0.0,0.0,1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if(viewMode==2) {
                gluPerspective(45.0,1,1,50);
                gluLookAt(pos[0],pos[1],pos[2],pos[0]+ver[0],pos[1]+ver[1],pos[2]+ver[2],0,0,1);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
        }
        else{
                //3Ddependeci
                glOrtho(-mazeSize-2.5, mazeSize+2.5, -mazeSize-2.5, mazeSize+2.5, -mazeSize-4.5, mazeSize+4.5);
                glMatrixMode(GL_MODELVIEW);
        }
        //3Ddependeci
        glShadeModel(GL_FLAT);
        //tranparanceDependeci
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
}

void drawBox(float zPlus,float zMin,float left,float down,float right,float top,float colR,float colG,float colB,float colAlpha) {
        glColor4f(colR,colG,colB,colAlpha);
        //depan
        //x1 1 y1 2 x2 3
        glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glVertex3f (left,down,zPlus);
        glVertex3f (right,down,zPlus);
        glVertex3f (right,top,zPlus);
        glVertex3f (left,top,zPlus);
        glEnd();
        //belakang
        glBegin(GL_POLYGON);
        glNormal3f(0,0,-1);
        glVertex3f (left,down,zMin);
        glVertex3f (right,down,zMin);
        glVertex3f (right,top,zMin);
        glVertex3f (left,top,zMin);
        glEnd();
        glColor4f(colR+0.2,colG+0.2,colB+0.2,colAlpha);
        //kiri
        glBegin(GL_POLYGON);
        glNormal3f(-1,0,0);
        glVertex3f (left,down,zPlus);
        glVertex3f (left,top,zPlus);
        glVertex3f (left,top,zMin);
        glVertex3f (left,down,zMin);
        glEnd();
        //kanan
        glBegin(GL_POLYGON);
        glNormal3f(1,0,0);
        glVertex3f (right,down,zPlus);
        glVertex3f (right,down,zMin);
        glVertex3f (right,top,zMin);
        glVertex3f (right,top,zPlus);
        glEnd();
        //bawah
        glBegin(GL_POLYGON);
        glNormal3f(0,-1,0);
        glVertex3f (left,down,zPlus);
        glVertex3f (left,down,zMin);
        glVertex3f (right,down,zMin);
        glVertex3f (right,down,zPlus);
        glEnd();
        //atas
        glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
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

void putMaterial(float r,float g,float b, float a) {
        GLfloat mat_specular[] = { r, g, b, a };
        GLfloat mat_shininess[] = { 10.0 };
        GLfloat mat_diffuse[] = { r, g, b, a };
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
}

void drawPlayer() {
        putMaterial(0.0, 1.0, 0.0, 1.0);
        glPushMatrix();
        if (playerType==0) {
                glTranslatef(xPlayer+0.5,yPlayer+0.5,0);
                //glutSolidCube(1);
                glutSolidSphere(0.5,20,10);
        }else{
                glTranslatef(xPlayer+0.5,yPlayer+0.5,-0.5);
                glutSolidCone(0.4,1, 50, 50);
        }
        glPopMatrix();
        //ManualPlayer
        //drawBox(0.5,-0.5,xPlayer,yPlayer,xPlayer+1,yPlayer+1,0,1,1,1;
}
void drawEnemy() {
        putMaterial(0.0, 1.0, 1.0, 1.0);
        glPushMatrix();
        glTranslatef(xEnemy+0.5,yEnemy+0.5,-0.5);
        glutSolidCone(0.5,1, 50, 50);
        glPopMatrix();
}
void setNim() {
        //TODO: seting up ctm nim only
        putMaterial(1.0, 0.0, 0.0, 1.0);
        glPushMatrix();
        if (viewMode!=0) {
                glTranslated(0.5+xNim,0.5+yNim,0);
                glRotatef(xNimRot,1,0,0);
                glRotatef(yNimRot,0,1,0);
                glRotatef(zNimRot,0,0,1);
                //glScalef(0.8,0.8,1);
                glTranslated(-0.5-xNim,-0.5-yNim,0);
        }
        drawNim();
        glPopMatrix();
}
void setDisplay(){
        //TODO: seting up ctm display only
        glPushMatrix();
        //glTranslatef(mazeSize+0.5,mazeSize+0.5,0);
        if (viewMode==1) {
                glRotatef(yRot,0,1,0);
                glRotatef(xRot,1,0,0);
        }
        glTranslatef(-mazeSize-0.5,-mazeSize-0.5,0);
}

void helperRoad(int xRoad,int yRoad){
        glBegin(GL_POLYGON);
        //x,y
        glColor3f(0,1,0);
        glVertex3f (xRoad,yRoad,0.0);
        glVertex3f (xRoad+1,yRoad, 0.0);
        glVertex3f (xRoad+1,yRoad+1, 0.0);
        glVertex3f (xRoad,yRoad+1, 0.0);
        glEnd();
}

void display(){
        //TODO: drawing the maze player nim and transparent floor
        myinit();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        setDisplay();
        isTrans == true ? putMaterial(0.0,0.0,0.8,0.3) : putMaterial(0.0,0.0,0.8,1.0);
        for (int i = 0; i < myMaze.getSize(); i++) {
                for (int j = 0; j < myMaze.getSize(); j++) {
                        if (Map[i][j]==1) {
                                drawBox(0.5,-0.5,j,i,j+1,i+1,0.1,0.1,0.1,1);
                        }
                }
        }
        setNim();
        //player
        drawPlayer();
        //enemy
        drawEnemy();
        //floor
        putMaterial(1, 1, 1, 0.5);
        drawBox(-0.51,-0.61,0,0,mazeSize*2+1,mazeSize*2+1,0.6,0.6,0.6,0.4);
        glPopMatrix();
        glutSwapBuffers();
}

void Timer (int iUnused){
        if (isEnemyrun && yEnemy != 0) {
                if (TransMap[yEnemy][xEnemy-1] == 2) {
                        TransMap[yEnemy][xEnemy] = 0;
                        xEnemy-=1;
                }
                else if (TransMap[yEnemy][xEnemy+1] == 2) {
                        TransMap[yEnemy][xEnemy] = 0;
                        xEnemy+=1;
                }
                else if (TransMap[yEnemy+1][xEnemy] == 2) {
                        TransMap[yEnemy][xEnemy] = 0;
                        yEnemy+=1;
                }
                else {
                        TransMap[yEnemy][xEnemy] = 0;
                        yEnemy-=1;
                }
                glutPostRedisplay();
                if (xEnemy==inDoor && yEnemy==0) {
                        isEnemyrun=false;
                }
                glutTimerFunc(500,Timer,0);
        }
}
void nimAnimation() {
        //CHANGED: change angle size of rotation (animation)
        if(rotBy == 0) {xNimRot += 0.1; }
        if(rotBy == 1) {yNimRot += 0.1; }
        if(rotBy == 2) {zNimRot += 0.1; }
        glutPostRedisplay();
}

void input(unsigned char key, int x, int y){
        if (key=='c' || key=='C') {
                settingUp(mazeSize);
        }
        if(key=='1') {
                if (amb == true) {
                        GLfloat ambient_light[] = { 0.5, 0.5, 0.5, 1.0 };
                        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
                        amb=false;
                }else{
                        GLfloat ambient_light[] = { 0.9, 0.9, 0.9, 1.0 };
                        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
                        amb=true;
                }
        }
        if(key=='2') {
                if(diff==true) {
                        glDisable(GL_LIGHT0);
                        diff=false;
                }else {
                        glEnable(GL_LIGHT0);
                        diff=true;
                }
        }
        if(key=='3') {
                if(spec==true) {
                        glDisable(GL_LIGHT1);
                        spec=false;
                }else {
                        glEnable(GL_LIGHT1);
                        spec=true;
                }
        }
        if(key=='4' ) {
                isMorning == true ? isMorning = false : isMorning = true;
        }
        if(key=='5') {
                isTrans == true ? isTrans = false : isTrans = true;
        }
        if(key==32) {
                isEnemyrun == true ? isEnemyrun = false : isEnemyrun = true;
                Timer(0);
        }
        if (key=='+' || key=='-') {
                key == '+' ? mazeSize+=1 : mazeSize-=1;
                settingUp(mazeSize);
        }
        if(key=='p' || key=='P') {
                if (playerType==0) {
                        playerType=1;
                }else{
                        playerType=0;
                }
        }
        if(key=='v' || key=='V') {
                //FIXME: rotation is wutever
                if(viewMode==0) {
                        glutIdleFunc(nimAnimation);
                        viewMode = 1;
                }else if(viewMode==1) {
                        viewMode = 2;
                }else{
                        glutIdleFunc(NULL);
                        viewMode = 0;
                }
        }
        //TODO: to control player walk inside maze & collision
        if((key=='w' || key=='W') && yPlayer < myMaze.getLength()*2 && Map[yPlayer+1][xPlayer] != 1) {
                yPlayer+=1;
        }
        if((key=='a' || key=='A') && Map[yPlayer][xPlayer-1] != 1) {
                xPlayer-=1;
        }
        if((key=='s' || key=='S') && yPlayer > 0 && Map[yPlayer-1][xPlayer] != 1) {
                yPlayer-=1;
        }
        if((key=='d' || key=='D') && Map[yPlayer][xPlayer+1] != 1) {
                xPlayer+=1;
        }
        //TODO: rotation of maze y or x
        if((key=='i' || key=='I' ) && viewMode==1) {
                xRot-=1;
        }
        if((key=='j' || key=='J' ) && viewMode==1) {
                yRot-=1;
        }
        if((key=='k' || key=='K' ) && viewMode==1) {
                xRot+=1;
        }
        if((key=='l' || key=='L' ) && viewMode==1) {
                yRot+=1;
        }
        display();
}

void mouse(int button, int state, int x, int y){
        //CHANGED: change direction of nim rotation
        switch (button) {
        case GLUT_LEFT_BUTTON:
                if (state == GLUT_DOWN && viewMode!=0) {rotBy=0; }
                break;
        case GLUT_MIDDLE_BUTTON:
                if (state == GLUT_DOWN && viewMode!=0) {rotBy=2; }
                break;
        case GLUT_RIGHT_BUTTON:
                if (state == GLUT_DOWN && viewMode!=0) {rotBy=1; }
                break;
        default:
                break;
        }
}

void settingLight() {
        GLfloat light_position_diff[] = { 10.0, 10.0, 5.0, 0.0};
        GLfloat light_position_spec[] = { 10.0, -10.0, 5.0, 0.0 };
        GLfloat diffuse_light[] = { 0.8, 0.8, 1.0, 0.5 };
        GLfloat specular_light[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat ambient_light[] = { 0.9, 0.9, 0.9, 1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, light_position_diff);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
        glLightfv(GL_LIGHT1, GL_POSITION, light_position_spec);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
        glEnable(GL_LIGHTING);
        glShadeModel (GL_SMOOTH);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
}
void specKey(int key, int x, int y){
        if (viewMode == 2) {
                if(key == GLUT_KEY_RIGHT ) {
                        alpha-=0.1;
                        ver[0] = cos(alpha);
                        ver[1] = sin(alpha);
                }else if(key == GLUT_KEY_LEFT) {
                        alpha+=0.1;
                        ver[0] = cos(alpha);
                        ver[1] = sin(alpha);
                }else if(key == GLUT_KEY_UP) {
                        pos[0]+=0.05*ver[0];
                        pos[1]+=0.05*ver[1];
                        pos[2]+=0.05*ver[2];
                }else if(key == GLUT_KEY_DOWN) {
                        pos[0]-=0.05*ver[0];
                        pos[1]-=0.05*ver[1];
                        pos[2]-=0.05*ver[2];
                }
                display();
        }
}
int main(int argc, char* argv[]){
        srand(time(NULL));
        srand((unsigned)time(0));
        settingUp(8);
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(500,500);
        glutCreateWindow("Maze IV || Kruskal Algorithm");
        Timer(0);
        glutDisplayFunc(display);
        glutSpecialFunc(specKey);
        glutKeyboardFunc(input);
        glutMouseFunc(mouse);
        myinit();
        settingLight();
        glutMainLoop();
        return 0;
}
