#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <inttypes.h>
#include "cfbgfx.hpp"

using namespace std;

const int scrw = 1280;
const int scrh = 720;

class Keyboard {
    public:
    char *k = strdup("   ");
    void update() {
        cInkey(k);
    }
};

char *temp1 = strdup("                              ");
char *temp2 = strdup("                              ");
char *temp3 = strdup("                              ");
char *temp4 = strdup("                              ");

class Mouse {
    public:
    int32_t wh = 0;
    int32_t lx = 0;
    int32_t ly = 0;
    int32_t x = 0;
    int32_t y = 0;
    int32_t cl = 0;
    int32_t lcl = 0;
    void update() {
        lcl=cl;
        lx=x;
        ly=y;
        cGetmouse (x,y,wh,cl);
    }
};

Mouse mouse;
Keyboard keyboard;

class FpsManager {
    public:

    double timval = 0;
    double timevalold = 0;

    int32_t frames = 0;
    int32_t fps = 0;
    double prevtime = 0;
    
    FpsManager() {
        timval=cTimer();
        timevalold=timval;
    }
    
    void update() {
        timval=cTimer();
        timval-=timevalold;
        timevalold=cTimer();
        timval*=60;
        //fps counter
        frames+=1;
        if (cTimer()-1>prevtime) { fps=frames;frames=0;prevtime=cTimer();}
    }
};

FpsManager fpsmanager;



double projectx(double inputvalx,double inputvaly) {
	return (inputvalx+inputvaly);
}

double projecty(double inputvalx,double inputvaly) {
	return (inputvaly-inputvalx);
}

#include "isoloop.hpp"
#include "camera.hpp"
#include "userinterface.hpp"
#include "graphic.hpp"
#include "map.hpp"
#include "agent.hpp"
#include "action.hpp"
#include "render.hpp"
#include "floodfill.hpp"
#include "colops.hpp"
#include "paint.hpp"
