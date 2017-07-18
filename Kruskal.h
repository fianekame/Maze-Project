#include <iostream>
#include <stdlib.h>

class Kruskal {
private:
int length;
int arrSize;
int** Map;
int* avaiRoad;
int total,xRand,yRand,temp,walk;

public:
// constructor
Kruskal(int l) {
        srand ( time(NULL) );
        length = l;
        arrSize = length*2+1;
};

void initArray(){
        avaiRoad = new int[4];
        Map = new int*[arrSize];
        for(int i = 0; i < arrSize; ++i) {
                Map[i] = new int[arrSize];
        }
}

void wallBreaker(int xRand2, int yRand2, int xRand1, int yRand1){
        Map[xRand1][yRand1] = 0;
        temp = Map[xRand2][yRand2];
        for (int i = 0; i < arrSize; i++) {
                for (int j = 0; j < arrSize; j++) {
                        if (Map[i][j] == temp) {
                                Map[i][j] = Map[xRand][yRand];
                        }
                }
        }
        walk--;
}

void cekAvailableRoad() {
        total = 0;
        if(xRand+2 <= length*2-1) {
                if (Map[xRand+2][yRand] != Map[xRand][yRand]) {
                        avaiRoad[total]=0;
                        total=total+1;
                }
        }
        if (xRand-2 >= 0) {
                if (Map[xRand-2][yRand] != Map[xRand][yRand]) {
                        avaiRoad[total]=1;
                        total=total+1;
                }
        }
        if (yRand+2 <= length*2-1) {
                if (Map[xRand][yRand+2] != Map[xRand][yRand]) {
                        avaiRoad[total]=2;
                        total=total+1;
                }
        }
        if (yRand-2 >= 0) {
                if (Map[xRand][yRand-2] != Map[xRand][yRand]) {
                        avaiRoad[total]=3;
                        total=total+1;
                }
        }
}

void goWalk(){
        cekAvailableRoad();
        //xRand+ bwah xRand- atas yRand+kanan yRand-kiri
        if (total > 0) {
                int direct = avaiRoad[rand() % total];
                switch (direct) {
                case 0:
                        wallBreaker(xRand+2,yRand,xRand+1,yRand);
                        break;
                case 1:
                        wallBreaker(xRand-2,yRand,xRand-1,yRand);
                        break;
                case 2:
                        wallBreaker(xRand,yRand+2,xRand,yRand+1);
                        break;
                case 3:
                        wallBreaker(xRand,yRand-2,xRand,yRand-1);
                        break;
                }
        }
}

void doGenerate() {
        initArray();
        walk = length*length-1;
        int x = 2;
        for (int i = 0; i < arrSize; i++) {
                for (int j = 0; j < arrSize; j++) {
                        if (i % 2 == 0 || j % 2 == 0) {
                                Map[i][j] = 1;
                        }
                        else{
                                Map[i][j] = x;
                                x++;
                        }
                }
        }
        while (walk != 0) {
                xRand = (rand() % length+1)*2-1;
                yRand = (rand() % length+1)*2-1;
                goWalk();
        }
};

void changeParam(){
        for (int i = 0; i < arrSize; i++) {
                for (int j = 0; j < arrSize; j++) {
                        if (Map[i][j] != 1) {
                                Map[i][j] = 0;
                        }
                }
        }
}

int** getMap() {
        changeParam();
        return Map;
};

int getDorPos(){
        if (length%2==0) {
                return length+1;
        }else{
                return length;
        }
};

int getLength(){
        return length;
}

int getSize(){
        return arrSize;
};
};
