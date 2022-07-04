
class painter{
    public:
	uint32_t frame = 0;
	uint32_t angle = 0;
	int32_t x = 400;
	int32_t y = 300;
	int32_t zm = 10;
	graphic * sprite = 0;
	uint32_t * picture = 0;
	uint32_t col = cRGB(255,255,255);
	uint32_t bcol= 0;
	int32_t tool = 0;
    char * toolname = strdup(temp1);


    void render() {
        cMultiPut (0,x,y,picture,zm,zm);
        
        cLine (0,0,0,100,20, col,bf);
        cLine (0,100,0,200,20,bcol,bf);
        
        strcpy(temp2,"frame: ");
        convertStr(frame+1,temp1);
        strcat(temp2,temp1);
        cDrawString (0,210,0, temp2,col);
        strcpy(temp2,"angle: ");
        convertStr(angle+1,temp1);
        strcat(temp2,temp1);
        cDrawString (0,210,10, temp2,col);
        
        cPset (0,mouse.x,mouse.y,col);
        cCircle (0,mouse.x,mouse.y,5);
        
        
        switch (tool) {
        case 0:
            strcpy(toolname,"pencil");
            break;
        case 1:
            strcpy(toolname,"fill");
            break;
        case 2:
            strcpy(toolname,"color picker");
            break;
        case 3:
            strcpy(toolname,"line");
            break;
        case 4:
            strcpy(toolname,"circle");
            break;
        case 5:
            strcpy(toolname,"square");
            break;
        }
        cDrawString (0,mouse.x+10,mouse.y-5, toolname, col);
    }

    void edit (){
        
        picture=sprite->img.at(frame).at(angle);
        
        int32_t w;
        int32_t h;
        w=cImageWidth(picture);
        h=cImageHeight(picture);
        
        int32_t ex;
        int32_t ey;
        int32_t lex;
        int32_t ley;
        ex = (((mouse.x -(zm/2.0))-x)/zm)+(w/2.0) +0.5;
        ey = (((mouse.y -(zm/2.0))-y)/zm)+(h/2.0) +0.5;
        lex= (((mouse.lx-(zm/2.0))-x)/zm)+(w/2.0) +0.5;
        ley= (((mouse.ly-(zm/2.0))-y)/zm)+(h/2.0) +0.5;

        uint32_t tcol;
        if (mouse.cl==1) {
            switch (tool) {
            case 0:
                cLine (picture,ex,ey,lex,ley,col);
                break;
            case 1:
                tcol = cPoint(picture,ex,ey);
                flood_fill(picture,ex,ey,tcol,col);
                break;
            case 2:
                col=cPoint(picture,ex,ey);
                break;
            }
            mouse.cl=0;mouse.lcl=0;
        }
        else if (mouse.cl==2) {
            switch (tool) {
            case 0:
                cLine (picture,ex,ey,lex,ley,bcol);
                break;
            case 1:
                tcol=cPoint(picture,ex,ey);
                flood_fill(picture,ex,ey,tcol,bcol);
                break;
            case 2:
                bcol=cPoint(picture,ex,ey);
                break;
            }
            mouse.cl=0;mouse.lcl=0;
        }
        
        if (mouse.cl==4) { x+=mouse.x-mouse.lx;y+=mouse.y-mouse.ly;mouse.cl=0;mouse.lcl=0; }
        
        
        if (*keyboard.k=='p') { tool=0;*keyboard.k=' '; }
        if (*keyboard.k=='f') { tool=1;*keyboard.k=' '; }
        if (*keyboard.k=='k') { tool=2;*keyboard.k=' '; }
        
        double th = 0;
        double ts = 0;
        double tv = 0;
        rgb_to_hsv(th,ts,tv,col);

        if (*keyboard.k=='7') { th+=0.05;*keyboard.k=' ';}
        if (*keyboard.k=='8') { ts+=0.05;*keyboard.k=' ';}
        if (*keyboard.k=='9') { tv+=0.05;*keyboard.k=' ';}
        if (*keyboard.k=='4') { th-=0.05;*keyboard.k=' ';}
        if (*keyboard.k=='5') { ts-=0.05;*keyboard.k=' ';}
        if (*keyboard.k=='6') { tv-=0.05;*keyboard.k=' ';}
        if (th>0.95) { th=0.95; }
        if (ts>1) { ts=1; }
        if (tv>1) { tv=1; }
        if (th<0) { th=0; }
        if (ts<0) { ts=0; }
        if (tv<0) { tv=0; }
        col=hsv_to_rgb(th,ts,tv);

        if (*keyboard.k=='[' && frame>0) { frame-=1;*keyboard.k=' ';}
        if (*keyboard.k==']' && frame<sprite->frames) { frame+=1;*keyboard.k=' ';}

        if (*keyboard.k=='=' && zm<20) { zm+=1;*keyboard.k=' ';}
        if (*keyboard.k=='-' && zm>1) { zm-=1;*keyboard.k=' ';}
        
        if (*keyboard.k=='s') { sprite->savefile();*keyboard.k=' ';}
        
        sprite->updatedark();
        
    }



};
