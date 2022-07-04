
void render(map &map1,camera &cam,vector<graphic> &tileset,vector<graphic> &agent_tiles,vector<agent> &agents,int32_t player) {
    int32_t px = 0;
    int32_t py = 0;
    int32_t mtx = 0;
    int32_t mty = 0;
    mtx=projectx((-cam.y+(cam.view_height/2))/30,(cam.x-(cam.view_width/2))/60);
    mty=projecty((-cam.y+(cam.view_height/2))/30,(cam.x-(cam.view_width/2))/60);


    isoloop.init((cam.view_width/60)+2,(cam.view_height/15)+4,mtx-1,mty-2,0,map1.tiles.size()-1,0,map1.tiles.at(0).size()-1);
    while (isoloop.finish()!=1) {
        int32_t x=isoloop.x;
        int32_t y=isoloop.y;
        px=projectx(x,y)*30 -cam.x+(cam.view_width/2)-30;
        py=projecty(x,y)*15 -cam.y+(cam.view_height/2)-15;


        if (map1.tiles.at(x).at(y).unfogged==true) {
                //tileset(2).render (cam,px,py)
                tileset.at(map1.tiles.at(x).at(y).grfkind).render(cam,px,py-30);
            }
        else if (map1.tiles.at(x).at(y).explored==true) {
                //tileset(2).render (cam,px,py,true)
                tileset.at(map1.tiles.at(x).at(y).grfkind).render(cam,px,py-30,true);
        }
            

        //if map1.tiles(x,y).unfogged=true then
        //   tileset(0).render (cam,px,py)
        //    'tileset(0).zPut (cam,px,py-tileset(0).h+30,py+30)
        //elseif map1.tiles(x,y).explored=true then
        //    tileset(0).render(cam,px,py,true)
        //    'tileset(0).zPut (cam,px,py-tileset(0).h+30,py+30)
        //end if
        
    }


    isoloop.init((cam.view_width/60)+2,(cam.view_height/15)+11,mtx-1,mty-2,0,map1.tiles.size()-1,0,map1.tiles.at(0).size()-1);
    while (isoloop.finish()!=1) {
        int32_t x=isoloop.x;
        int32_t y=isoloop.y;
        px=projectx(x,y)*30 -cam.x+(cam.view_width/2)-30;
        py=projecty(x,y)*15 -cam.y+(cam.view_height/2)-15;

        if (map1.tiles.at(x).at(y).unfogged==true) {
            if (map1.tiles2.at(x).at(y).grfkind>=0) {
                tileset.at(map1.tiles2.at(x).at(y).grfkind).render (cam,px,py-tileset.at(map1.tiles2.at(x).at(y).grfkind).h,false,py,true);
            }
        }
        else if (map1.tiles.at(x).at(y).explored==true) {
            if (map1.tiles2.at(x).at(y).grfkind>=0) {
                tileset.at(map1.tiles2.at(x).at(y).grfkind).render (cam,px,py-tileset.at(map1.tiles2.at(x).at(y).grfkind).h,true,py,true);
            }
        }
            
    }



    //sort agents
    //---------------------------------
    int32_t rendorder[agents.size()];
    int32_t orderpy[agents.size()];
    for (uint32_t i=0; i < agents.size(); i++) {
        orderpy[i]=projecty(agents.at(i).x,agents.at(i).y)*15 -cam.y+(cam.view_height/2)-15;
    }
    for (uint32_t i=0; i < agents.size(); i++) {
        rendorder[i]=i;
        for (uint32_t j=0; j < agents.size(); j++) {
            if (orderpy[j]<orderpy[i]) { rendorder[i]=j; }
        }
        orderpy[rendorder[i]]=99999;
    }
    //--------------------------------

    for (uint32_t j=0; j < agents.size(); j++) {
        int32_t i=rendorder[j];
        px=projectx(agents.at(i).x,agents.at(i).y)*30 -cam.x+(cam.view_width/2)-30;
        py=projecty(agents.at(i).x,agents.at(i).y)*15 -cam.y+(cam.view_height/2)-15;
        if (i==player) {
            switch (agents.at(i).animstate) {
            case 0:
                agent_tiles.at(0).render(cam,px,py-agent_tiles.at(0).h,false,py,true,true,agents.at(i).ang,agents.at(i).frame);
            case 1:
                agent_tiles.at(1).render(cam,px,py-agent_tiles.at(1).h,false,py,true,true,agents.at(i).ang,agents.at(i).frame);
            case 2:
                agent_tiles.at(2).render(cam,px,py-agent_tiles.at(2).h,false,py,true,true,agents.at(i).ang,agents.at(i).frame);
            case 3:
                agent_tiles.at(3).render(cam,px,py-agent_tiles.at(3).h,false,py,true,true,agents.at(i).ang,agents.at(i).frame);
            }
        }
        else {
            if (map1.tiles.at(round(agents.at(i).x)).at(round(agents.at(i).y)).unfogged==true) {
                agents.at(player).makememory(agents.at(i).x,agents.at(i).y,i,agents.at(i).team,cTimer()+10,agents.at(i).ang);
        
                switch (agents.at(i).animstate) {
                case 0:
                    agent_tiles.at(0).render(cam,px,py-agent_tiles.at(0).h,false,py,true,true,agents.at(i).ang,agents.at(i).frame);
                case 1:
                    agent_tiles.at(1).render(cam,px,py-agent_tiles.at(1).h,false,py,true,true,agents.at(i).ang,agents.at(i).frame);
                case 2:
                    agent_tiles.at(2).render(cam,px,py-agent_tiles.at(2).h,false,py,true,true,agents.at(i).ang,agents.at(i).frame);
                case 3:
                    agent_tiles.at(3).render(cam,px,py-agent_tiles.at(3).h,false,py,true,true,agents.at(i).ang,agents.at(i).frame);
                }
            }
            else if (agents.at(player).findmemory(i)>=0) {
                int32_t kl=agents.at(player).findmemory(i);
                px=projectx(agents.at(player).agentmemories[kl].x,agents.at(player).agentmemories[kl].y)*30 -cam.x+(cam.view_width/2)-30;
                py=projecty(agents.at(player).agentmemories[kl].x,agents.at(player).agentmemories[kl].y)*15 -cam.y+(cam.view_height/2)-15;
                agent_tiles.at(0).render(cam,px,py-agent_tiles.at(0).h,false,py,true,true,agents.at(player).agentmemories[kl].ang,gdouble,0,0,100,0);
            }
        }
    }

}

