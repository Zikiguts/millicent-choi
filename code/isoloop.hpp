#include <inttypes.h>

class IsoLoop {
    public:
    int32_t lbx=0;
    int32_t lby=0;
    int32_t ubx=60;
    int32_t uby=60;
    int32_t xp=0;
    int32_t yp=0;
    int32_t mw=32;
    int32_t mh=24;
    int32_t xs;
    int32_t ys;
    int32_t x;
    int32_t y;
    int32_t d;
    int32_t i;
    int32_t j;
	


    void init(int32_t mw2,int32_t mh2,int32_t xs2,int32_t ys2,int32_t lbx2,int32_t ubx2,int32_t lby2,int32_t uby2) {
        lbx=lbx2;lby=lby2;ubx=ubx2;uby=uby2;
        xp=0;yp=0;
        mw=mw2;mh=mh2;
        xs=xs2;ys=ys2;
        x=xs;y=ys;d=0;
        i=0;j=0;

        if (x<lbx) { finish();}
        if (x>ubx) { finish();}
        if (y<lby) { finish();}
        if (y>uby) { finish();}
    }


    int32_t finish() {
        do {
            i+=1;
            x+=1;
            y+=1;
            if (i > mw) {
                if (d == 1) {
                    xp-=1;
                    d=0;
                }
                else {
                    yp+=1;
                    d=1;
                }
                y=ys+yp;
                x=xs+xp;
                i=0;
                j+=1;
                if (j > mh) { return 1;}
            }
        } while (x<lbx || y<lby || x>ubx || y>uby);

        return 0;
    }

};

IsoLoop isoloop;
