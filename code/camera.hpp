
class camera {
    public:
	double zm = 0;
	double x = 0;
	double y = 0;
	int32_t view_x = 0;
	int32_t view_y = 0;
	int32_t view_width = 0;
	int32_t view_height = 0;
	
    int32_t view_width_const = 0;
	int32_t view_height_const = 0;
    
	uint32_t * scr = 0;
	uint8_t * scrpixels = 0;
	int32_t pitch = 0;
	
	uint32_t * zbufptr = 0;

    camera() {
        view_width=scrw;
        view_height=scrh;
        view_width_const=view_width;
        view_height_const=view_height;
        scr=cImageCreate(view_width,view_height);
        
        scrpixels=cImagePixels(scr);
        pitch=cImagePitch(scr);
        //uint32_t zbuf = malloc[view_width][view_height];
        zbufptr = (uint32_t*) malloc(sizeof(uint32_t)*view_width*view_height);
        zm=1;
        cLine (scr,0,0,view_width,view_height,cRGBA(0,0,0,0),bf);
        clearzbuf();
    }

    camera(int32_t w, int32_t h) {
        view_width=w;
        view_height=h;
        view_width_const=view_width;
        view_height_const=view_height;
        scr=cImageCreate(view_width,view_height);
        
        scrpixels=cImagePixels(scr);
        pitch=cImagePitch(scr);
        
        //uint32_t zbuf = malloc[view_width][view_height];
        zbufptr = (uint32_t*) malloc(sizeof(uint32_t)*view_width*view_height);
        zm=1;
        cLine (scr,0,0,view_width,view_height,cRGBA(0,0,0,0),bf);
        clearzbuf();
    }

    void zoom(double factor) {
        cImageDestroy(scr);
        view_width=view_width_const/factor;
        view_height=view_height_const/factor;
        scr=cImageCreate(view_width,view_height);

        scrpixels=cImagePixels(scr);
        pitch=cImagePitch(scr);
        
        //uint32_t zbuf = malloc[view_width][view_height];
        free(zbufptr);
        zbufptr = (uint32_t*) malloc(sizeof(uint32_t)*view_width*view_height);
        zm=factor;
        cLine (scr,0,0,view_width,view_height,cRGBA(0,0,0,0),bf);
        clearzbuf();
    }

    void control() {
        if (cMultikey(17)) {y-=4/zm*fpsmanager.timval;}
        if (cMultikey(31)) {y+=4/zm*fpsmanager.timval;}
        if (cMultikey(30)) {x-=4/zm*fpsmanager.timval;}
        if (cMultikey(32)) {x+=4/zm*fpsmanager.timval;}
    }

    void followdouble(double xx,double yy) {
        x=projectx(xx,yy)*30;
        y=(projecty(xx,yy)*15)-60;
    }

    void clearzbuf() {
        memset(zbufptr,0,view_width*view_height*sizeof(uint32_t)); // clears zbuffer to 0
        /*
        for i as long=0 to ubound(zbuf,1)*ubound(zbuf,2)
        zbufptr[i]=0
        next*/
    }

    void render() {
        cMultiPut (0,view_x+(view_width/2)*zm,view_y+(view_height/2)*zm,scr,zm,zm);
        //put (0,0),scr,pset
        //line scr,(0,0)-(view_width,view_height),rgba(0,0,0,0),bf
        clearzbuf();
        memset(scrpixels, 30, pitch*view_height);

    }

    ~camera() {
        cImageDestroy(scr);
        free(zbufptr);
    }

};
