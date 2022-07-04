
class tile {
    public:
	int32_t grfkind = 0;
	bool wall = false;
	bool visionblock = false;
	bool unfogged = false;
	bool explored = false;
};

class tilelayer {
    public:
	int32_t grfkind = 0;
};

class map{
    public:
	int32_t map_width = 0;
	int32_t map_height = 0;
    vector<vector<tile>> tiles;
    vector<vector<tilelayer>> tiles2;

    
    void load(char * file) {
        
        fstream data_file;
        data_file.open(file, fstream::in | fstream::binary);
        data_file.read((char*)&map_width, sizeof(map_width));
        data_file.read((char*)&map_height, sizeof(map_height));
        map_width+=1;map_height+=1;
        for (int32_t x = 0; x < map_width; x++) {
            tiles.push_back(vector<tile>());
            tiles2.push_back(vector<tilelayer>());
            for (int32_t y = 0; y < map_height; y++) {
                tiles.at(x).push_back(tile());
                tiles2.at(x).push_back(tilelayer());
                data_file.read((char*)&tiles.at(x).at(y), sizeof(tiles.at(x).at(y)));
                data_file.read((char*)&tiles2.at(x).at(y), sizeof(tiles2.at(x).at(y)));
            }
        }

        data_file.close();
        
        /*Dim As Long fnum = FreeFile()
        dim as long p=1
        
        open file for binary as #fnum
        get #fnum,p,map_width:p+=sizeof(map_width)
        get #fnum,p,map_height:p+=sizeof(map_height)
        redim tiles(map_width,map_height) as tile
        redim tiles2(map_width,map_height) as tilelayer
        
        for x as long=0 to map_width
            for y as long=0 to map_height
                get #fnum,p,tiles(x,y):p+=sizeof(tile)
                get #fnum,p,tiles2(x,y):p+=sizeof(tilelayer)
            next
        next
        close #fnum*/
    }


    void save(char * file) {
        /*Dim As Long fnum = FreeFile()
        dim as long p=1
        
        open file for binary as #fnum
        put #fnum,p,map_width:p+=sizeof(map_width)
        put #fnum,p,map_height:p+=sizeof(map_height)

        for x as long=0 to map_width
            for y as long=0 to map_height
                put #fnum,p,tiles(x,y):p+=sizeof(tile)
                put #fnum,p,tiles2(x,y):p+=sizeof(tilelayer)
            next
        next
        close #fnum*/
    }






    void create() {
        map_width = 500;
        map_height = 500;
        for (int32_t x = 0; x < map_width; x++) {
            tiles.push_back(vector<tile>());
            tiles2.push_back(vector<tilelayer>());
            for (int32_t y = 0; y < map_height; y++) {
                tiles.at(x).push_back(tile());
                tiles2.at(x).push_back(tilelayer());
                if (x==0 || y==0 || x==map_width || y==map_height) {
                    tiles2.at(x).at(y).grfkind=42;
                    tiles.at(x).at(y).grfkind=0;
                    tiles.at(x).at(y).wall=true;
                    tiles.at(x).at(y).visionblock=true;
                }
                else {
                    tiles2.at(x).at(y).grfkind=-1;
                    tiles.at(x).at(y).grfkind=0;
                    tiles.at(x).at(y).wall=false;
                    tiles.at(x).at(y).visionblock=false;
                }
            }
        }
    }
    
    void clone (map &map1) {
        map_width=map1.map_width;
        map_height=map1.map_height;
        for (int32_t x = 0; x < map_width; x++) {
            tiles.push_back(vector<tile>());
            tiles2.push_back(vector<tilelayer>());
            for (int32_t y = 0; y < map_height; y++) {
                tiles.at(x).push_back(tile());
                tiles2.at(x).push_back(tilelayer());
            }
        }
    }
    
    void fog(bool value) {
        for (int32_t x=0; x< map_width; x++) {
            for (int32_t y=0; y< map_height; y++) {
                tiles.at(x).at(y).unfogged=value;
            }
        }
    }

    void unfog(int32_t x,int32_t y,int32_t dov){
        
        int32_t cx=x;
        int32_t cy=y;
        int32_t cxl=cx-dov;
        int32_t cxh=cx+dov;
        int32_t cyl=cy-dov;
        int32_t cyh=cy+dov;

        for (int32_t yy=cyl; yy < cy; yy++) {
            for (int32_t xx=cxl; xx < cx; xx++) {
                
                int32_t dist=abs(sqrt(((xx-cx)^2)+((yy-cy)^2)));
                if (dist<dov) {
                    int32_t yy2=yy;
                    for (int32_t vdv=0; vdv < 1; vdv++) {
                        if (yy2<0) {
                            yy2=0;
                        }
                        else if (yy2>map_height) {
                            yy2=map_height;
                        }
                        int32_t xs=xx;
                        int32_t xf=cxl+cxh-xx;
                        if (xs<0) { xs=0;}
                        if (xf>map_width) { xf=map_width;}
                        for (int32_t xx2=xs; xx2< xf; xx2++) {
                            if (tiles.at(xx2).at(yy2).unfogged==false) {
                                tiles.at(xx2).at(yy2).unfogged=true;
                                tiles.at(xx2).at(yy2).explored=true;
                            }
                        }
                        yy2=cyl+cyh-yy;
                    }
                    xx=cx;
                }

            }
        }
        
    }

};

