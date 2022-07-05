#define getR( c ) (  (uint32_t)c  >> 16 & 255 )
#define getG( c ) (  (uint32_t)c  >>  8 & 255 )
#define getB( c ) (  (uint32_t)c        & 255 )
#define getA( c ) (  (uint32_t)c  >> 24       )

class graphic {
    public:
	uint32_t h = 0;
	uint32_t w = 0;
	uint32_t frames = 0;
	double curframe = 0;
	double speed = 0;
	char * filename = strdup(temp1);
	uint32_t angles = 0;
	uint32_t start = 0;
	
    vector<vector<uint32_t *>> img;
    vector<vector<uint32_t *>> dk;
	//img(any,any) as any ptr 'frames,0 or 8
	//dk(any,any) as any ptr
    

    uint32_t darken ( uint32_t source_pixel, uint32_t destination_pixel, void * parameter ) {
        if (source_pixel!=cRGB(255,0,255)) {
            return cRGBA(getR(source_pixel)/1.2,getG(source_pixel)/1.2,getB(source_pixel)/1.2,getA(source_pixel));
        }
        else {
            return destination_pixel;
        }
    }

    void initdark() {
        for (uint32_t f=0; f <= frames; f++) {
            for (uint32_t ang=0; ang <= angles; ang++) {
                dk.at(f).at(ang)=cImageCreate(w,h,cRGBA(255,0,255,0));
                /*put dk(f,ang),(0,0),img(f,ang),custom,@darken*/
                cPut (dk.at(f).at(ang),0,0,img.at(f).at(ang),Darken);
            }
        }
    }

    void updatedark() {
        for (uint32_t f=0; f <= frames; f++) {
            for (uint32_t ang=0; ang <= angles; ang++) {
                /*put dk(f,ang),(0,0),img(f,ang),custom,@darken*/
                cPut (dk.at(f).at(ang),0,0,img.at(f).at(ang),Darken);
            }
        }
    }


    void loadfile(char * namestr) {
        speed=0.1;
        strcpy(filename,namestr);

        /*
        Dim As Long filenum = FreeFile()
        Open filename+"anim" For input As #filenum
            input #filenum, frames,start,angles
        Close #filenum

        redim img(frames,angles) as any ptr
        */
        strcpy(temp1,filename);
        strcat(temp1,"anim");
        
        fstream file;
        file.open(temp1, ios_base::in);
        //char mychar=' ';
        
        string element;
        getline(file,element,',');
        strcpy(temp1,element.c_str());
        frames=convertInt(temp1);
        
        getline(file,element,',');
        strcpy(temp1,element.c_str());
        start=convertInt(temp1);
        
        getline(file,element,',');
        strcpy(temp1,element.c_str());
        angles=convertInt(temp1);
        
        file.close();
        
        cPrintInt(frames);
        cPrintInt(start);
        cPrintInt(angles);
        cFlip();
        //cSleep();
        //img.resize(frames+1);
        //dk.resize(frames+1);
        //img.at(0).resize(angles+1);
        //dk.at(0).resize(angles+1);
        
        
        if (start<10) {
            strcpy(temp1,"000");
            convertStr(start,temp2);
            strcat(temp1,temp2);
        }
        else if (start<100) {
            strcpy(temp1,"00");
            convertStr(start,temp2);
            strcat(temp1,temp2);
        }
        else if (start<1000) {
            strcpy(temp1,"0");
            convertStr(start,temp2);
            strcat(temp1,temp2);
        }
        strcpy(temp3,filename);
        strcat(temp3,"1/");
        strcat(temp3,temp1);
        strcat(temp3,".bmp");
        fstream data_file;
        data_file.open(temp3 , fstream::in | fstream::binary);
            int32_t a;
            data_file.read((char*)&a, 18);
            data_file.read((char*)&w, sizeof(w));
            data_file.read((char*)&h, sizeof(h));
        data_file.close();

        
        for (uint32_t k = start; k <= start+frames; k++) {
            img.push_back(vector<uint32_t *>());
            dk.push_back(vector<uint32_t *>());
            for (uint32_t direc = 0; direc <= angles; direc++) {
                img.at(k-start).push_back(0);
                dk.at(k-start).push_back(0);
                if (k<10) {
                    strcpy(temp1,"000");
                    convertStr(k,temp2);
                    strcat(temp1,temp2);
                }
                else if (k<100) {
                    strcpy(temp1,"00");
                    convertStr(k,temp2);
                    strcat(temp1,temp2);
                }
                else if (k<1000) {
                    strcpy(temp1,"0");
                    convertStr(k,temp2);
                    strcat(temp1,temp2);
                }
                img.at(k-start).at(direc) = cImageCreate( w, h,cRGB(255,0,255) );
                strcpy(temp3,filename);
                convertStr(direc+1,temp4);
                strcat(temp3,temp4);
                strcat(temp3,"/");
                strcat(temp3,temp1);
                strcat(temp3,".bmp");
                cBload (temp3, img.at(k-start).at(direc));
            }
        }

        initdark();
    }

    void savefile() {
            /*dim as string numstr
            if start<10 then
                numstr="000"+str(start)
            elseif start<100 then
                numstr="00"+str(start)
            elseif start<1000 then
                numstr="0"+str(start)
            end if
            
            mkdir filename
            
            for direc as long=0 to angles
                for k as long=start to start+frames
                    if k<10 then
                        numstr="000"+str(k)
                    elseif k<100 then
                        numstr="00"+str(k)
                    elseif k<1000 then
                        numstr="0"+str(k)
                    end if
                    mkdir filename+str(direc+1)+"/"
                    bsave filename+str(direc+1)+"/"+numstr+".bmp", img(k-start,direc)
                next
            next
            
            Dim As Long filenum = FreeFile()
            Open filename+"anim" For output As #filenum
                write #filenum, frames,start,angles
            Close #filenum*/
    }


    ~graphic () {
        for (uint32_t f = 0; f<img.size(); f++ ) {
            for (uint32_t d = 0; d<img.at(0).size(); d++ ) {
                cImageDestroy(img.at(f).at(d));
                cImageDestroy(dk.at(f).at(d));
            }
        }
    }



    void render(camera &cam,int32_t x,int32_t y,bool dark =false,uint32_t z =0, bool zsorton =false, bool zfront =false, double ang =0,double &frame = gdouble,uint8_t r =0,uint8_t g =0,uint8_t b =0,uint8_t a =0) {
        int32_t direc=(ang*(angles+1))/360;
        if ((double)direc>angles) { direc=0;}
        double framebackup=curframe;
        if (frame>-1) {
            if (frame>frames) { frame=0;}
            curframe=frame;
        }
        if (zsorton==false) {
            if (dark==true) {
                cPut (cam.scr,x,y,dk.at(curframe).at(direc),Trans);
            }
            else {
                cPut (cam.scr,x,y,img.at(curframe).at(direc),Trans);
            }
        }
        else {

            
            uint8_t * destptr;
            uint8_t * srcptr;
            int32_t w;
            int32_t h;
            int32_t w2;
            int32_t h2;
            int32_t bypp;
            int32_t pitch;
            int32_t bypp2;
            int32_t pitch2;
            w=cImageWidth(cam.scr);
            h=cImageHeight(cam.scr);
            bypp=cImageBypp(cam.scr);
            pitch=cImagePitch(cam.scr);
            destptr=cam.scrpixels;
            if (dark==false) {
                w2=cImageWidth(img.at(curframe).at(direc));
                h2=cImageHeight(img.at(curframe).at(direc));
                bypp2=cImageBypp(img.at(curframe).at(direc));
                pitch2=cImagePitch(img.at(curframe).at(direc));
                srcptr=cImagePixels(img.at(curframe).at(direc));
            }
            else {
                w2=cImageWidth(dk.at(curframe).at(direc));
                h2=cImageHeight(dk.at(curframe).at(direc));
                bypp2=cImageBypp(dk.at(curframe).at(direc));
                pitch2=cImagePitch(dk.at(curframe).at(direc));
                srcptr=cImagePixels(dk.at(curframe).at(direc));
            }
            int32_t xs;
            int32_t ys;
            int32_t xf;
            int32_t yf;
            int32_t ind1;
            int32_t ind2;
            int32_t iy1;
            int32_t iy2;
            int32_t ix1;
            int32_t ix2;
            int32_t i=0;
            h2-=1;w2-=1;h-=1;w-=1;
            xs=x;
            ys=y;
            xf=x+w2;
            yf=y+h2;
            if (xs<0)  {xs=0;}
            if (ys<0)  {ys=0;}
            if (xf>w)  {xf=w;}
            if (yf>h)  {yf=h;}
            ix1=xs*bypp;
            ix2=(xs-x)*bypp2;
            iy1=ys*pitch;
            iy2=(ys-y)*pitch2;
   
            if (zfront==false) {
                for (int32_t yy=ys; yy < yf; yy++) {
                    i=0;
                    for (int32_t xx=xs; xx < xf; xx++) {
                        ind1=ix1+iy1+i;
                        ind2=ix2+iy2+i;

                        if (z>=cam.zbufptr[xx+(yy*cam.view_width)]) {
                            if (srcptr[ind2]==255 && srcptr[ind2+1]==0 && srcptr[ind2+2]==255) {
                            
                            }
                            else {
                                destptr[ind1]=srcptr[ind2];
                                destptr[ind1+1]=srcptr[ind2+1];
                                destptr[ind1+2]=srcptr[ind2+2];
                                destptr[ind1+3]=srcptr[ind2+3];
                                cam.zbufptr[xx+(yy*cam.view_width)]=z;
                            }
                        }
                        i+=bypp;
                    }
                    iy1+=pitch;
                    iy2+=pitch2;
                }
            }
            else {
                for (int32_t yy=ys; yy < yf; yy++) {
                    i=0;
                    for (int32_t xx=xs; xx < xf; xx++) {
                        ind1=ix1+iy1+i;
                        ind2=ix2+iy2+i;

                        if (srcptr[ind2]!=255 || srcptr[ind2+1]!=0 || srcptr[ind2+2]!=255) {
                            if (r==0 && g==0 && b==0 && a==0) {
                                if (z>=cam.zbufptr[xx+(yy*cam.view_width)]) {
                                    destptr[ind1]=srcptr[ind2];
                                    destptr[ind1+1]=srcptr[ind2+1];
                                    destptr[ind1+2]=srcptr[ind2+2];
                                    destptr[ind1+3]=srcptr[ind2+3];
                                    cam.zbufptr[xx+(yy*cam.view_width)]=z;
                                }
                                else {
                                    //destptr[ind1]/=2'blue
                                    //destptr[ind1+1]/=2'green
                                    //destptr[ind1+2]/=2'red
                                    //destptr[ind1+3]/=2'alpha
                                    destptr[ind1]/=2;//blue
                                    destptr[ind1+1]/=2;//green
                                    destptr[ind1+2]/=2;//red
                                    destptr[ind1+3]/=2;//alpha
                                    //destptr[ind1+2]+=100'red
                                }
                            }
                            else {
                                destptr[ind1]/=2;
                                destptr[ind1+1]/=2;
                                destptr[ind1+2]/=2;
                                destptr[ind1+3]/=2;
                                destptr[ind1]+=b;
                                destptr[ind1+1]+=g;
                                destptr[ind1+2]+=r;
                                destptr[ind1+3]+=a;
                                if (z>=cam.zbufptr[xx+(yy*cam.view_width)]) {
                                    cam.zbufptr[xx+(yy*cam.view_width)]=z;
                                }
                            }
                        }
                        i+=bypp;
                    }
                    iy1+=pitch;
                    iy2+=pitch2;
                }
            }

        }
        curframe=framebackup;
    }

    void animate() {
        curframe+=speed*fpsmanager.timval;
        if (curframe>frames) { curframe=0;}
    }

};
