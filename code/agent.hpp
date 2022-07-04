
double piover180 = 0.0174532925;


int32_t check2(int32_t x,int32_t y,vector<vector<tile>> &array) {
    if (x>=0 && y>=0 && (uint32_t)x<=array.size()-1 && (uint32_t)y<=array.at(0).size()-1) {
        if (array.at(x).at(y).wall==true) { return 1; }
    }
    else {
        return 1;
    }
    return 0;
}

int32_t collide(int32_t xx1,int32_t yy1,int32_t xx2,int32_t yy2,vector<vector<tile>> &array) {
    double xnew;
    double ynew;
    double dx;
    double dy;
    double x3;
    double y3;
    double x2;
    double y2;
    //double ynum;
    double den;
    double num;
    double numadd;
    double xinc1;
    double xinc2;
    double yinc1;
    double yinc2;
    x3 = xx1 ; y3 = yy1 ; x2 = xx2 ; y2 = yy2;
    dx = abs(x2 - x3) ; dy = abs(y2 - y3) ; xnew = x3 ; ynew = y3;
   
    if (x2 >= x3) { xinc1 = 1 ; xinc2 = 1 ;} else {xinc1 = -1 ; xinc2 = -1;}
    if (y2 >= y3) { yinc1 = 1 ; yinc2 = 1 ;} else {yinc1 = -1 ; yinc2 = -1;}
   
    if (dx >= dy) {
        xinc1 = 0 ; yinc2 = 0 ; den = dx ; num = dx / 2 ; numadd = dy;
    }
    else {
        xinc2 = 0 ; yinc1 = 0 ; den = dy ; num = dy / 2 ; numadd = dx;
    }
    
    while (1) {
		if (check2(xnew,ynew,array)==1) { return 1;}
		if (xnew==x2 && ynew==y2) { return 0;}
        num += numadd;
        if (num >= den) {
			num -= den ; xnew += xinc1 ; ynew += yinc1;
			if (check2(xnew,ynew,array)==1) { return 1;}
        }
        xnew += xinc2 ; ynew += yinc2;
       
    }
    return 0;
}





int32_t check(int32_t x,int32_t y,map &array,map &array2) {
    if (x>=0 && y>=0 && (uint32_t)x<=array.tiles.size()-1 && (uint32_t)y<=array.tiles.at(0).size()-1) {
        if (array2.tiles[x][y].visionblock==false) {
            array.tiles[x][y].grfkind=array2.tiles[x][y].grfkind;
            array.tiles2[x][y].grfkind=array2.tiles2[x][y].grfkind;
            array.tiles[x][y].unfogged=true;
            array.tiles[x][y].explored=true;
        }
        else {
            array.tiles[x][y].grfkind=array2.tiles[x][y].grfkind;
            array.tiles2[x][y].grfkind=array2.tiles2[x][y].grfkind;
            array.tiles[x][y].unfogged=true;
            array.tiles[x][y].explored=true;
            return 1;
        }
    }
    else {
        return 1;
    }
    return 0;
    
}

int32_t check22(int32_t x,int32_t y,map &array,map &array2) {
    if (x>=0 && y>=0 && (uint32_t)x<=array.tiles.size()-1 && (uint32_t)y<=array.tiles.at(0).size()-1) {
        if (array2.tiles[x][y].visionblock==true) {
            array.tiles[x][y].grfkind=array2.tiles[x][y].grfkind;
            array.tiles2[x][y].grfkind=array2.tiles2[x][y].grfkind;
            array.tiles[x][y].unfogged=true;
            array.tiles[x][y].explored=true;
            return 1;
        }
    }
    else {
        return 1;
    }
    return 0;

}


int32_t scanline(int32_t xx1,int32_t yy1,int32_t xx2,int32_t yy2,map &array,map &array2) {
    double xnew;
    double ynew;
    double dx;
    double dy;
    double x3;
    double y3;
    double x2;
    double y2;
    //double ynum;
    double den;
    double num;
    double numadd;
    double xinc1;
    double xinc2;
    double yinc1;
    double yinc2;
    x3 = xx1 ; y3 = yy1 ; x2 = xx2 ; y2 = yy2;
    dx = abs(x2 - x3) ; dy = abs(y2 - y3) ; xnew = x3 ; ynew = y3;
   
    if (x2 >= x3) { xinc1 = 1 ; xinc2 = 1 ;} else {xinc1 = -1 ; xinc2 = -1;}
    if (y2 >= y3) { yinc1 = 1 ; yinc2 = 1 ;} else {yinc1 = -1 ; yinc2 = -1;}
   
    if (dx >= dy) {
        xinc1 = 0 ; yinc2 = 0 ; den = dx ; num = dx / 2 ; numadd = dy;
    }
    else {
        xinc2 = 0 ; yinc1 = 0 ; den = dy ; num = dy / 2 ; numadd = dx;
    }
   
   
    while (1) {
		if (check(xnew,ynew,array,array2)==1) { return 1;}
		if (xnew==x2 && ynew==y2) { return 0;}
        num += numadd;
        if (num >= den) {
			num -= den ; xnew += xinc1 ; ynew += yinc1;
			if (check(xnew,ynew,array,array2)==1) {
                xnew += xinc2 ; ynew += yinc2;
                check22(xnew,ynew,array,array2);
                return 1;
			}
        }
        xnew += xinc2 ; ynew += yinc2;
       
    }
}

void explore(int32_t x,int32_t y,double ang,int32_t dist,int32_t wide,map &array,map &array2) {
    int32_t xx1=x;
    int32_t yy1=y;
    int32_t xx2=x;
    int32_t yy2=y;
    xx1+=sin((ang+wide)*piover180)*dist;
    yy1-=cos((ang+wide)*piover180)*dist;
    xx2+=sin((ang-wide)*piover180)*dist;
    yy2-=cos((ang-wide)*piover180)*dist;
    double xnew;
    double ynew;
    double dx;
    double dy;
    double x3;
    double y3;
    double x2;
    double y2;
    //double ynum;
    double den;
    double num;
    double numadd;
    double xinc1;
    double xinc2;
    double yinc1;
    double yinc2;
    x3 = xx1 ; y3 = yy1 ; x2 = xx2 ; y2 = yy2;
    dx = abs(x2 - x3) ; dy = abs(y2 - y3) ; xnew = x3 ; ynew = y3;
   
    if (x2 >= x3) { xinc1 = 1 ; xinc2 = 1 ;} else {xinc1 = -1 ; xinc2 = -1;}
    if (y2 >= y3) { yinc1 = 1 ; yinc2 = 1 ;} else {yinc1 = -1 ; yinc2 = -1;}
   
    if (dx >= dy) {
        xinc1 = 0 ; yinc2 = 0 ; den = dx ; num = dx / 2 ; numadd = dy;
    }
    else {
        xinc2 = 0 ; yinc1 = 0 ; den = dy ; num = dy / 2 ; numadd = dx;
    }
   
    while(1) {
		scanline(x,y,xnew,ynew,array,array2);
		if (xnew==x2 && ynew==y2) { break;}
        num += numadd;
        if (num >= den) { num -= den ; xnew += xinc1 ; ynew += yinc1;}
        xnew += xinc2 ; ynew += yinc2 ;
       
    }
}

class agentmemory{
    public:
    bool active = false;
    double x = 0;
    double y = 0;
    int32_t agentid = 0;
    int32_t team = 0;
    double timev = 0;
    double ang = 0;
};


class agent{
    public:
	double x = 0;
	double y = 0;
	double ang = 0;
	double ang2 = 0;
    int32_t team = 0;
    agentmemory agentmemories[9];
	map mapinfo = map();
	map * globalmap;
	double frame = 0;
	double speed = 0;

	int32_t animstate = 0;
	//control
	bool forward = false;
	bool crouch = false;
	bool bike = false;
	bool turn_left = false;
	bool turn_right = false;
    
    void makememory(double x2, double y2, int32_t i2,int32_t team2,double timev2,double ang2) {
        for (int32_t i=0; i<9; i++) {
            if (agentmemories[i].agentid==i2) {
                agentmemories[i].active=true;
                agentmemories[i].x=x2;
                agentmemories[i].y=y2;
                agentmemories[i].agentid=i2;
                agentmemories[i].team=team2;
                agentmemories[i].timev=timev2;
                agentmemories[i].ang=ang2;
                break; break; break;
            }
        }
        for (int32_t i=0; i<9; i++) {
            if (agentmemories[i].active==false) {
                agentmemories[i].active=true;
                agentmemories[i].x=x2;
                agentmemories[i].y=y2;
                agentmemories[i].agentid=i2;
                agentmemories[i].team=team2;
                agentmemories[i].timev=timev2;
                agentmemories[i].ang=ang2;
                break; break; break;
            }
        }
        int32_t olt=0;
        for (int32_t i=0; i<9; i++) {
            if (agentmemories[i].timev<agentmemories[olt].timev) { olt=i;}
        }
        agentmemories[olt].active=true;
        agentmemories[olt].x=x2;
        agentmemories[olt].y=y2;
        agentmemories[olt].agentid=i2;
        agentmemories[olt].team=team2;
        agentmemories[olt].timev=timev2;
        agentmemories[olt].ang=ang2;
    }

    int32_t findmemory(int32_t i2) {
        for (int32_t i=0; i<9; i++) {
            if (cTimer()<agentmemories[i].timev) {
                if (agentmemories[i].agentid==i2) { return i;}
            }
            else {
                agentmemories[i].active=false;
            }
        }
        return -1;
    }
    
    
    
    void move() {
        
        if (animstate==0) {
            frame+=0.04*fpsmanager.timval;
        }
        else if (animstate==1) {
            frame+=0.5*fpsmanager.timval;
        }
        else if (animstate==2) {
            frame+=0.3*fpsmanager.timval;
        }
        else if (animstate==3) {
            frame=3;//+=0.3*fpsmanager.timval;
        }
        
        if (turn_left==true) { ang-=1*fpsmanager.timval;}
        if (turn_right==true) { ang+=1*fpsmanager.timval;}

        while (ang2>=360){ ang2-=360;}
        while (ang2<0){ ang2+=360;}

        while (ang>=360){ ang-=360;}
        while (ang<0){ ang+=360;}


        if (bike==true) {
            if (speed>0) {
                int32_t j=ang-ang2;
                int32_t j2=ang2-ang;
                while (j>=-180){ j-=360;}
                while (j<180){ j+=360;}
                while (j2>=-180){ j2-=360;}
                while (j2<180){ j2+=360;}
                if (j>=j2) { ang-=2*fpsmanager.timval;}
                if (j<j2) { ang+=2*fpsmanager.timval;}
                if (j>j2+30) { frame=4;}
                if (j<j2-30) { frame=2;}
                if (j>j2+40) { frame=5;}
                if (j<j2-40) { frame=1;}
                if (j>j2+50) { frame=6;}
                if (j<j2-50) { frame=0;}
            }
        }
        else {
            ang=ang2;
        }



        if (forward==true || bike==true) {
            animstate=1;
            if (bike==false) { speed=0.08;}
            if (crouch==true) { speed=0.03;animstate=2;}
            if (bike==true) {
                if (forward==true && speed<0.08*6) {
                    speed+=0.005*fpsmanager.timval;
                }
                else if (speed>0) {
                    speed-=0.01*fpsmanager.timval;
                }
                animstate=3;
            }
            double lx;
            double ly;
            double clx;
            double cly;
            clx=x;
            cly=y;
            
            lx=x;
            x+=sin(ang*piover180)*speed*fpsmanager.timval;
            if (x>lx && collide(round(x+0.5),round(y)    ,round(lx),round(y),globalmap->tiles)==1) { x=lx;speed-=0.015*fpsmanager.timval;}
            if (x<lx && collide(round(x-0.5),round(y)    ,round(lx),round(y),globalmap->tiles)==1) { x=lx;speed-=0.015*fpsmanager.timval;}
            if (x>lx && collide(round(x+0.5),round(y+0.4),round(lx),round(y),globalmap->tiles)==1) { x=lx;speed-=0.015*fpsmanager.timval;}
            if (x<lx && collide(round(x-0.5),round(y+0.4),round(lx),round(y),globalmap->tiles)==1) { x=lx;speed-=0.015*fpsmanager.timval;}
            if (x>lx && collide(round(x+0.5),round(y-0.4),round(lx),round(y),globalmap->tiles)==1) { x=lx;speed-=0.015*fpsmanager.timval;}
            if (x<lx && collide(round(x-0.5),round(y-0.4),round(lx),round(y),globalmap->tiles)==1) { x=lx;speed-=0.015*fpsmanager.timval;}
            
            ly=y;
            y-=cos(ang*piover180)*speed*fpsmanager.timval;
            if (y>ly && collide(round(x)    ,round(y+0.5),round(x),round(ly),globalmap->tiles)==1) { y=ly;speed-=0.015*fpsmanager.timval;}
            if (y<ly && collide(round(x)    ,round(y-0.5),round(x),round(ly),globalmap->tiles)==1) { y=ly;speed-=0.015*fpsmanager.timval;}
            if (y>ly && collide(round(x+0.4),round(y+0.5),round(x),round(ly),globalmap->tiles)==1) { y=ly;speed-=0.015*fpsmanager.timval;}
            if (y<ly && collide(round(x+0.4),round(y-0.5),round(x),round(ly),globalmap->tiles)==1) { y=ly;speed-=0.015*fpsmanager.timval;}
            if (y>ly && collide(round(x-0.4),round(y+0.5),round(x),round(ly),globalmap->tiles)==1) { y=ly;speed-=0.015*fpsmanager.timval;}
            if (y<ly && collide(round(x-0.4),round(y-0.5),round(x),round(ly),globalmap->tiles)==1) { y=ly;speed-=0.015*fpsmanager.timval;}
            if (speed<0) { speed=0;}
            
            if (clx-x>-0.01 && clx-x<0.01 && cly-y>-0.01 && cly-y<0.01) {
                if (bike==false) { animstate=0;}
            }
        }
        else {
            animstate=0;
        }

            if (x<0) { x=0;}
            if (y<0) { y=0;}
            
            
            if (x>globalmap->map_width) { x=globalmap->map_width;}
            if (y>globalmap->map_height) { y=globalmap->map_height;}

        explore(round(x),round(y),ang,10,30,mapinfo,*globalmap);

    }
    
    void control() {
        if (cMultikey(30)) { turn_left=true; } else {turn_left=false;}
        if (cMultikey(32)) { turn_right=true; } else {turn_right=false;}
        if (cMultikey(17)) { forward=true; } else {forward=false;}
        if (cMultikey(16)) { crouch=true; } else {crouch=false;}
        if (*keyboard.k=='q') {
            if (bike==true) {bike=false;} else {bike=true;}
            *keyboard.k=' ';
        }
    }

};



