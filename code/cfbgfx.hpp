
extern "C" {
        enum RasterOp
        {
            PSet    = 0,
            PReset  = 1,
            Trans   = 2,
            And     = 3,
            Or      = 4,
            Xor     = 5,
            Alpha   = 6,
            Darken  = 7
        };
        enum LineBox
        {
            l    = 0,
            b  = 1,
            bf   = 2
        };

      const int32_t GFX_NULL               = -1;
      const int32_t GFX_WINDOWED         = 0x00;
      const int32_t GFX_FULLSCREEN         = 0x01;
      const int32_t GFX_OPENGL            = 0x02;
      const int32_t GFX_NO_SWITCH         = 0x04;
      const int32_t GFX_NO_FRAME         = 0x08;
      const int32_t GFX_SHAPED_WINDOW      = 0x10;
      const int32_t GFX_ALWAYS_ON_TOP      = 0x20;
      const int32_t GFX_ALPHA_PRIMITIVES   = 0x40;
      const int32_t GFX_HIGH_PRIORITY      = 0x80;
        
      double gdouble = 0.0;
    
      extern int32_t cScreenRes(int32_t dx, int32_t dy, int32_t depth = 32, int32_t pages = 0, int32_t flags = 0);
      #define ScreenRes cScreenRes
      extern int32_t cWindowTitle(char * text);
      extern uint32_t * cImageCreate(int32_t x, int32_t y, uint32_t color = 0, int32_t depth = 32);
      extern int32_t cImageDestroy(uint32_t * img);
      extern int32_t cBload(char * file,uint32_t * img);
      extern int32_t cPset(uint32_t * target,int32_t x, int32_t y, uint32_t color = 0);
      extern uint32_t cPoint(uint32_t * target,int32_t x, int32_t y);
      extern uint32_t cRGB(int32_t r, int32_t g, int32_t b);
      extern uint32_t cRGBA(int32_t r, int32_t g, int32_t b, int32_t a);
      extern int32_t cCircle(uint32_t * target, int32_t x, int32_t y, int32_t size, uint32_t color=0, int32_t fill=0);
      extern int32_t cLine(uint32_t * target,int32_t x1,int32_t y1,int32_t x2,int32_t y2,uint32_t color=0,uint32_t box=l, int32_t style=0b1111111111111111);
	  extern int32_t cBox(uint32_t * target,int32_t x1,int32_t y1,int32_t x2,int32_t y2,uint32_t color=0,int32_t fill=0,int32_t style=0b1111111111111111);
	  extern int32_t cPrint(char * text,int32_t mode=0);
      extern int32_t cPrintInt(int32_t val,int32_t mode=0);
	  #define Print cPrint
	  extern int32_t cLocate(int32_t column, int32_t row);
	  extern int32_t cColor(uint32_t fore, uint32_t back);
	  extern int32_t cPaint32_t(uint32_t * target, int32_t x, int32_t y, uint32_t color, uint32_t border);
      extern int32_t cSleep(int32_t num = 0);
      extern int32_t cMultikey(int32_t key);
      extern int32_t cScreenlock();
      extern int32_t cScreenunlock();
      extern int32_t cCls();
      extern int32_t cPut(uint32_t * dest,int32_t x,int32_t y,uint32_t * img,int32_t mode);
      extern int32_t cSetmouse(int32_t mx=-1,int32_t my=-1,int32_t v=-1,int32_t c=-1);
      extern int32_t cGetmouse(int32_t &mx,int32_t &my, int32_t &mw,int32_t &mb);
      extern int32_t cDrawString(uint32_t * target,int32_t x,int32_t y, char * text, uint32_t col);
      extern double cTimer();
      extern int32_t cScreenControl(int32_t what, int32_t  param1 = 0x80000000, int32_t param2 = 0x80000000, int32_t param3 = 0x80000000, int32_t param4 = 0x80000000);
      extern int32_t cImageWidth ( uint32_t * image);  
      extern int32_t cImageHeight ( uint32_t * image);  
      extern int32_t cImagePitch ( uint32_t * image);  
      extern int32_t cImageBypp ( uint32_t * image);  
      extern uint8_t * cImagePixels ( uint32_t * image);
      extern int32_t cFlip();
      extern int32_t cInkey(char * dest);
      extern int32_t cMultiPut(uint32_t * pTarget = 0, int32_t xMidPos = 0, int32_t yMidPos = 0, uint32_t * pSource = 0, double xScale = 1, double yScale = 1, double Rotate = 0, bool Transparent = false);
      extern int32_t cMid ( char * strv, char * dest , int32_t start , int32_t n = 0 );
      extern int32_t convertInt ( char * value );
      extern int32_t convertStr ( int32_t value, char * dest );
      extern int32_t cInstr ( int32_t start , char * strval, char * substring );
      extern int32_t cLen ( char * value );
}
