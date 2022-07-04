
class uitextbox {
    public:
    bool active = false;
    char * text = strdup(temp1);
    char * p1 = strdup(temp1);
    char * p2 = strdup(temp1);
    char * p3 = strdup(temp1);
    
    int32_t stringid = 0;
    int32_t x = 0;
    int32_t y = 0;
    int32_t w = 0;
    int32_t h = 0;
    bool autohide = false;

    void init(int32_t stringid2, double x1, double y1, double w1, double h1, bool autohide2 = false) {
        active=true;
        stringid=stringid2;
        x=scrw*0.5*x1;
        y=scrh*0.5*y1;
        w=scrw*0.5*w1*0.5;
        h=scrh*0.5*h1*0.5;
        autohide=autohide2;
    }

    void render(uint32_t * scr,vector<char *> &strings,vector<char *> &variablestrings) {
        if (active == true) {
            text = strcpy(text,strings.at(stringid));
            int32_t p = 0;
            do {
                p1 = strcpy(p1,"@v");
                p=cInstr(1,text, p1);
                if (p>0) {
                    p1 = strcpy(p1,"");
                    p2 = strcpy(p2,"");
                    p3 = strcpy(p3,"");
                    cMid(text,p1,1,p-1);
                    cMid(text,p2,p+2,4);
                    cMid(text,p3,p+6);
                    text = strcpy(text,"");
                    text = strcat(text,p1);
                    text = strcat(text,variablestrings.at(convertInt(p2)));
                    text = strcat(text,p3);
                }
            } while ( p!=0 );
            cLine (scr,x-w,y-h,x+w,y+h,cRGBA(0,0,0,150),bf);
            cLine (scr,x-w,y-h,x+w,y+h,cRGBA(255,255,255,80),b);
            cDrawString (scr,x-(cLen(text)*4),y-4,text,cRGBA(255,255,255,200));
            
            if (autohide==true) { active=false;}
        }
    }
};


class userinterface {
    public:
    vector<char *> strings;
    vector<uitextbox> textboxes;

    uint32_t * scr = 0;
    uint32_t * renderscr = 0;

    userinterface() {
        scr=cImageCreate(scrw*0.5,scrh*0.5,cRGBA(0,0,0,0));
        renderscr=cImageCreate(scrw,scrh,cRGBA(0,0,0,0));
        
        strings.resize(20);
        textboxes.resize(20);
        
    }



    void render(vector<char *> &variablestrings) {
        for (uint32_t i = 0; i < textboxes.size(); i++) {
            textboxes.at(i).render(scr,strings,variablestrings);
        }
        //mouse
        cCircle (scr,mouse.x*0.5,mouse.y*0.5,4,cRGB(255,255,255));


        cMultiPut (renderscr,scrw*0.5,scrh*0.5,scr,2,2,0,1);
        cPut (0,0,0,renderscr,Alpha);
        cLine (scr,0,0,scrw,scrh,cRGBA(0,0,0,0),bf);

    }




    ~userinterface() {
        cImageDestroy(scr);
        cImageDestroy(renderscr);
    }


};

