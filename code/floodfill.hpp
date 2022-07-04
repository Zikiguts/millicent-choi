int32_t flood_fill(uint32_t * img,int32_t x, int32_t y, uint32_t target, uint32_t fill_color) {
 
    int32_t x_max;
    int32_t y_max;
    x_max=cImageWidth(img);
    y_max=cImageHeight(img);
    x_max-=1;
    y_max-=1;
    if (x>x_max) { x=x_max; }
    if (y>y_max) { y=y_max; }
    // 0, 0 is top left corner
    if (target == fill_color) { return 0; }
    if (cPoint(img,x,y) != target) { return 0; }

    int32_t l = x;
    int32_t r = x;

    while (l -1 > -1 && cPoint(img, l -1, y) == target) {
        l-=1;
    }

    while (r +1 < x_max && cPoint(img, r +1, y) == target) {
        r+=1;
    }

    cLine (img,l,y,r,y, fill_color);
    for (x = l; x < r; x++) {
        if (y+1<y_max) { flood_fill(img,x,y+1,target,fill_color);}
        if (y-1>   -1) { flood_fill(img,x,y-1,target,fill_color);}
    }

    return 0;
}
