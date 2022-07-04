
#define getR( c ) (  (uint32_t)c  >> 16 & 255 )
#define getG( c ) (  (uint32_t)c  >>  8 & 255 )
#define getB( c ) (  (uint32_t)c        & 255 )
#define getA( c ) (  (uint32_t)c  >> 24       )

double min2(double v1 ,double v2 ,double v3 ) {
    double v=9999;
    if (v1<v) { v=v1;}
    if (v2<v) { v=v2;}
    if (v3<v) { v=v3;}
    return v;
}

double max2(double v1 ,double v2 ,double v3 ) {
    double v=-9999;
    if (v1>v) { v=v1;}
    if (v2>v) { v=v2;}
    if (v3>v) { v=v3;}
    return v;
}

//RGB to HSV
//RGB input range = 0-255
//HSV output range = 0-1.0
void rgb_to_hsv(double &H,double &S,double &V,uint32_t col) {
    double del_R;
    double del_G;
    double del_B;
    double var_R = ( (double)getR(col) / 255 );
    double var_G = ( (double)getG(col) / 255 );
    double var_B = ( (double)getB(col) / 255 );

    double var_Min = min2( var_R, var_G, var_B );    //Min. value of RGB
    double var_Max = max2( var_R, var_G, var_B );    //Max. value of RGB
    double del_Max = var_Max - var_Min;             //Delta RGB value

    V = var_Max;

    if (del_Max==0) {
        H = 0;
        S = 0;
    }
    else {
       S = del_Max / var_Max;

       del_R = ( ( ( var_Max - var_R ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;
       del_G = ( ( ( var_Max - var_G ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;
       del_B = ( ( ( var_Max - var_B ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;

        if  ( var_R == var_Max ) {
           H = del_B - del_G;
       }
        else if ( var_G == var_Max ) {
           H = ( 1.0 / 3.0 ) + del_R - del_B;
       }
        else if ( var_B == var_Max ) {
           H = ( 2.0 / 3.0 ) + del_G - del_R;
        }

        if ( H < 0 ) { H += 1; }
        if ( H > 1 ) { H -= 1; }
    }
}
//HSV to RGB
//HSV input range = 0-1.0
//RGB output range = 0-255
uint32_t hsv_to_rgb(double H,double S,double V) {
    double r;
    double g;
    double b;
    double var_h;
    double var_i;
    double var_1;
    double var_2;
    double var_3;
    if (S==0) {
       r = V * 255;
       g = V * 255;
       b = V * 255;
    }
    else {
       var_h = H * 6;
       if (var_h==6) { var_h = 0; }     //H must be < 1
       var_i = (int)var_h;             //Or ... var_i = floor( var_h )
       var_1 = V * ( 1 - S );
       var_2 = V * ( 1 - S * ( var_h - var_i ) );
       var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

       if     ( var_i == 0 ) {
           r = V     ; g = var_3 ; b = var_1;
       }
       else if ( var_i == 1 ) {
           r = var_2 ; g = V     ; b = var_1;
       }
       else if ( var_i == 2 ) {
           r = var_1 ; g = V     ; b = var_3;
       }
       else if ( var_i == 3 ) {
           r = var_1 ; g = var_2 ; b = V;
       }
       else if ( var_i == 4 ) {
           r = var_3 ; g = var_1 ; b = V;
       }  
       else {
           r = V    ; g = var_1 ; b = var_2;
       }

       r *=255;
       g *=255;
       b *=255;
    }

    return cRGB(r,g,b);
}
