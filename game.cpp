#include <string.h>
#include <cstdio>

#include "code/include.hpp"


int main(int32_t argc, char **argv) {
    
    cScreenControl (150,1);
    cScreenRes (scrw,scrh,32,GFX_OPENGL,2);
    
    userinterface ui = userinterface();

    vector<char *> variablestrings;
    for (int i = 0; i<20; i++) {
        variablestrings.push_back(strdup(temp1));
    }
    ui.strings[0]=strdup("press '@v0000' to use");
    ui.strings[1]=strdup("player position: x=@v0001 y=@v0002");
    ui.strings[2]=strdup("fps: @v0003");
    ui.strings[3]=strdup("Right click to remove object.");
    ui.strings[4]=strdup("Left click to place object.");
    ui.strings[5]=strdup("Press '-' and '=' to change object.");
    ui.strings[6]=strdup("You wake up cold and alone in a bright room.");
    ui.strings[7]=strdup("You get up to take a look around...");

    ui.textboxes[0].init(2,0.25,0.05,0.45,0.05);
    ui.textboxes[1].init(3,0.25,0.10,0.45,0.05);
    ui.textboxes[2].init(4,0.25,0.15,0.45,0.05);
    ui.textboxes[3].init(5,0.25,0.20,0.45,0.05);

    ui.textboxes[4].init(0,0.5,0.35,0.25,0.05,true);
    ui.textboxes[5].init(1,0.5,0.95,0.35,0.05);
    ui.textboxes[6].init(6,0.5,0.80,0.60,0.05);
    ui.textboxes[7].init(7,0.5,0.85,0.60,0.05);

    cSetmouse (-1,-1,0);

    vector<map> levels;
    levels.resize(1);
    //levels.at(0).create();
    levels.at(0).load(strcpy(temp1,"maps/map1"));

    vector<action> actions;
    actions.resize(5);

    strcpy(actions.at(0).namestr,"open door");
    actions.at(0).active=false;
    actions.at(0).triggers.resize(2);
    actions.at(0).outcomes.resize(3);
    actions.at(0).triggers.at(0).id1=0;
    actions.at(0).triggers.at(0).x=16;
    actions.at(0).triggers.at(0).y=4;
    actions.at(0).triggers.at(1).id1=0;
    actions.at(0).triggers.at(1).x=18;
    actions.at(0).triggers.at(1).y=4;
        
    actions.at(0).outcomes.at(0).x=17;
    actions.at(0).outcomes.at(0).y=4;
    actions.at(0).outcomes.at(0).val1=45;
    actions.at(0).outcomes.at(0).bool1=false;
    actions.at(0).outcomes.at(0).bool2=false;
        
    actions.at(0).outcomes.at(1).id=2;//activate
    actions.at(0).outcomes.at(1).bool1=true;
    actions.at(0).outcomes.at(1).id1=1;
    actions.at(0).outcomes.at(2).id=3;//set time
    actions.at(0).outcomes.at(2).id1=1;
    actions.at(0).outcomes.at(2).id2=0;
    actions.at(0).outcomes.at(2).timev=3;


    
    strcpy(actions.at(1).namestr,"close door");
    actions.at(1).active=false;
    actions.at(1).triggers.resize(1);
    actions.at(1).outcomes.resize(3);
    actions.at(1).triggers.at(0).id=1;
    
    actions.at(1).outcomes.at(0).x=17;
    actions.at(1).outcomes.at(0).y=4;
    actions.at(1).outcomes.at(0).val1=44;
    actions.at(1).outcomes.at(0).bool1=true;
    actions.at(1).outcomes.at(0).bool2=true;
    actions.at(1).outcomes.at(1).id=2;//activate
    actions.at(1).outcomes.at(1).bool1=true;
    actions.at(1).outcomes.at(1).id1=0;
    actions.at(1).outcomes.at(1).id2=0;
    actions.at(1).outcomes.at(2).id=2;//activate
    actions.at(1).outcomes.at(2).bool1=true;
    actions.at(1).outcomes.at(2).id1=0;
    actions.at(1).outcomes.at(2).id2=1;

    
    strcpy(actions.at(2).namestr,"when e pressed activate floor switch");
    actions.at(2).active=true;
    actions.at(2).triggers.resize(1);
    actions.at(2).outcomes.resize(3);
    actions.at(2).triggers.at(0).id=2;
    actions.at(2).triggers.at(0).id1=0;
    actions.at(2).triggers.at(0).x=15;
    actions.at(2).triggers.at(0).y=3;
    
    actions.at(2).outcomes.at(0).x=17;
    actions.at(2).outcomes.at(0).y=4;
    actions.at(2).outcomes.at(0).val1=44;
    actions.at(2).outcomes.at(0).bool1=true;
    actions.at(2).outcomes.at(0).bool2=true;
    actions.at(2).outcomes.at(1).id=2;//activate
    actions.at(2).outcomes.at(1).bool1=true;
    actions.at(2).outcomes.at(1).id1=0;
    actions.at(2).outcomes.at(2).id=2;//activate
    actions.at(2).outcomes.at(2).bool1=true;
    actions.at(2).outcomes.at(2).id1=4;

    
    strcpy(actions.at(3).namestr,"show message when by pc");
    actions.at(3).active=true;
    actions.at(3).triggers.resize(1);
    actions.at(3).outcomes.resize(2);
    actions.at(3).triggers.at(0).id1=0;
    actions.at(3).triggers.at(0).x=15;
    actions.at(3).triggers.at(0).y=3;
        
    actions.at(3).outcomes.at(0).id=5;//show text box
    actions.at(3).outcomes.at(0).id1=4;
    actions.at(3).outcomes.at(1).id=1;//reactivate
    

    strcpy(actions.at(4).namestr,"when e pressed deactivate floor switch");
    actions.at(4).active=false;
    actions.at(4).triggers.resize(1);
    actions.at(4).outcomes.resize(4);
    actions.at(4).triggers.at(0).id=2;
    actions.at(4).triggers.at(0).id1=0;
    actions.at(4).triggers.at(0).x=15;
    actions.at(4).triggers.at(0).y=3;
    
    actions.at(4).outcomes.at(0).x=17;
    actions.at(4).outcomes.at(0).y=4;
    actions.at(4).outcomes.at(0).val1=43;
    actions.at(4).outcomes.at(0).bool1=true;
    actions.at(4).outcomes.at(0).bool2=true;
    actions.at(4).outcomes.at(1).id=2;//activate
    actions.at(4).outcomes.at(1).bool1=false;
    actions.at(4).outcomes.at(1).id1=0;
    actions.at(4).outcomes.at(2).id=2;//activate
    actions.at(4).outcomes.at(2).bool1=true;
    actions.at(4).outcomes.at(2).id1=2;
    actions.at(4).outcomes.at(3).id=2;//activate
    actions.at(4).outcomes.at(3).bool1=false;
    actions.at(4).outcomes.at(3).id1=1;

    painter pixeleditor = painter();

    camera cam1 = camera();
    cam1.zoom(2);
    
    vector<graphic> agent_tiles;
    agent_tiles.resize(4);
    agent_tiles.at(0).loadfile(strcpy(temp1,"graphics/agents/choi/stand/"));
    agent_tiles.at(1).loadfile(strcpy(temp1,"graphics/agents/choi/run/"));
    agent_tiles.at(2).loadfile(strcpy(temp1,"graphics/agents/choi/crawl/"));
    agent_tiles.at(3).loadfile(strcpy(temp1,"graphics/agents/choi/ride/"));


    vector<graphic> tileset;
    tileset.resize(52);
    for (uint32_t i=0; i<tileset.size()-1; i++) {
        strcpy(temp2,"graphics/tiles/");
        convertStr(i+1,temp1);
        strcat(temp2,temp1);
        tileset.at(i).loadfile(strcat(temp2,"/"));
    }
    //for i as long=0 to 49
    //tileset(i).savefile
    //next

    vector<agent> agents;
    int32_t player=0;
    agents.resize(12);
    agents.at(player).x=14;agents.at(player).y=1;
    agents.at(1).x=12;agents.at(1).y=8;
    agents.at(2).x=11;agents.at(2).y=8;
    agents.at(3).x=12;agents.at(3).y=7;
    agents.at(4).x=2;agents.at(4).y=2;
    agents.at(5).x=3;agents.at(5).y=2;
    agents.at(6).x=4;agents.at(6).y=2;
    agents.at(7).x=2;agents.at(7).y=3;
    agents.at(8).x=3;agents.at(8).y=3;
    agents.at(9).x=4;agents.at(9).y=3;
    agents.at(10).x=2;agents.at(10).y=4;
    agents.at(11).x=3;agents.at(11).y=4;

    for (uint32_t i=0; i<agents.size(); i++) {
        agents.at(i).globalmap=&levels.at(0);
        agents.at(i).mapinfo.clone(levels.at(0));
    }
    
    int32_t editkind = 0;
    int32_t togglepaint = -1;

    while (not cMultikey(1)) { //Loop until Key 'Esc' is pressed
        strcpy(variablestrings.at(0),"e");
        convertStr(agents.at(player).x,temp1);
        strcpy(variablestrings.at(1),temp1);
        convertStr(agents.at(player).y,temp1);
        strcpy(variablestrings.at(2),temp1);
        convertStr(fpsmanager.fps,variablestrings.at(3));
        
        keyboard.update();
        fpsmanager.update();
        mouse.update();

        
        if (mouse.x != -1 && mouse.y != -1) {
        
            int32_t mtx;
            int32_t mty;
            mtx=projectx((-mouse.y/cam1.zm+(cam1.view_height/2)-cam1.y)/30,(mouse.x/cam1.zm-(cam1.view_width/2)+cam1.x)/60)-0.5;
            mty=projecty((-mouse.y/cam1.zm+(cam1.view_height/2)-cam1.y)/30,(mouse.x/cam1.zm-(cam1.view_width/2)+cam1.x)/60)+1.5;
            if (mtx<0) { mtx=0;}
            if (mty<0) { mty=0;}
            
            if (mtx>(int32_t)levels.at(0).tiles.size()-1) { mtx=levels.at(0).tiles.size()-1;}
            if (mty>(int32_t)levels.at(0).tiles.at(0).size()-1) { mty=levels.at(0).tiles.at(0).size()-1;}
        
            agents.at(player).ang2=(atan2(-agents.at(player).x+mtx,+agents.at(player).y-mty)/piover180);
        
            if (*keyboard.k=='y') { togglepaint=-togglepaint;pixeleditor.frame=0;pixeleditor.angle=0;*keyboard.k=' ';}
            
            if (togglepaint == 1) { //pixel editor
                pixeleditor.sprite=&tileset.at(editkind);
                pixeleditor.edit();
            }
            else {  //mapeditor
                if (mouse.cl==2) { levels.at(0).tiles2.at(mtx).at(mty).grfkind=-1;levels.at(0).tiles.at(mtx).at(mty).wall=false;levels.at(0).tiles.at(mtx).at(mty).visionblock=false;}
                if (mouse.cl==1) { levels.at(0).tiles2.at(mtx).at(mty).grfkind=editkind;levels.at(0).tiles.at(mtx).at(mty).wall=true;levels.at(0).tiles.at(mtx).at(mty).visionblock=true;}
                if (mouse.cl==4) { levels.at(0).tiles2.at(mtx).at(mty).grfkind=editkind;levels.at(0).tiles.at(mtx).at(mty).wall=true;levels.at(0).tiles.at(mtx).at(mty).visionblock=false;}
                if (cMultikey(19) && mouse.cl==4) { levels.at(0).tiles2.at(mtx).at(mty).grfkind=editkind;levels.at(0).tiles.at(mtx).at(mty).wall=false;levels.at(0).tiles.at(mtx).at(mty).visionblock=false;}

                if (*keyboard.k==' ') { levels.at(0).tiles.at(mtx).at(mty).grfkind=editkind;}
                if (*keyboard.k=='=' && editkind<(int32_t)tileset.size()-2) { editkind+=1;}
                if (*keyboard.k=='-' && editkind>0) { editkind-=1;}
                if (*keyboard.k=='s') { levels.at(0).save(strcpy(temp1,"maps/map1"));}
            }
        }
        
        if (*keyboard.k=='1') {cam1.zoom(2);}
        if (*keyboard.k=='2') {cam1.zoom(1);}
        if (*keyboard.k=='3') {cam1.zoom(0.5);}

        if (*keyboard.k=='c') { //add new graphic from current
            int32_t mxt = tileset.size();
            tileset.push_back(graphic());
            strcpy(temp2,"graphics/tiles/");
            convertStr(editkind+1,temp1);
            strcat(temp2,temp1);
            tileset.at(mxt).loadfile(strcat(temp2,"/"));
            strcpy(temp2,"graphics/tiles/");
            convertStr(mxt+1,temp1);
            strcat(temp2,temp1);
            tileset.at(mxt).filename=strcat(temp2,"/");
            tileset.at(mxt).savefile();
            editkind=mxt;
        }

        //cam1.control

        cam1.followdouble(agents.at(player).x,agents.at(player).y);
        for (uint32_t i = 0; i < agents.size(); i++) {
            agents.at(i).mapinfo.fog(false);
        }
        
        agents.at(player).control();
        
        
        for (uint32_t i = 0; i < agents.size(); i++) {
            agents.at(i).move();
        }

        for (uint32_t i = 0; i < actions.size(); i++) {
            actions.at(i).check(actions,agents,levels.at(0),ui);
        }

        //levels.at(0).unfog(mtx,mty,8);
        
        for (uint32_t i=0; i<tileset.size(); i++) {
            tileset.at(i).animate();
        }
        
        render(agents.at(player).mapinfo,cam1,tileset,agent_tiles,agents,player);

        tileset.at(editkind).render(cam1,0,60);
        
        

        //cScreenlock();
            cam1.render();
            ui.render(variablestrings);

            if (togglepaint==1) {pixeleditor.render();}
        //cScreenunlock();

        cFlip();
        cSleep(1);
    };
    
    //levels.at(0).save(strcpy(temp1,"maps/map1"));
    return 0;
}
