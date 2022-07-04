
class guide {
    public:
    char * id = strdup(temp1);
    char * id1 = strdup(temp1);
    char * id2 = strdup(temp1);
    char * x = strdup(temp1);
    char * y = strdup(temp1);
    char * timev = strdup(temp1);
    char * val1 = strdup(temp1);
    char * val2 = strdup(temp1);
    char * bool1 = strdup(temp1);
    char * bool2 = strdup(temp1);
};

guide triggerguide[2];
guide outcomeguide[5];
/*
triggerguide(0).id="If agent is on location x1 y1 then trigger outcomes"
triggerguide(0).x="location x"
triggerguide(0).y="location y"
triggerguide(0).id1="agent id"
triggerguide(1).id="If time reached then trigger outcomes"
triggerguide(1).timev="trigger time"
triggerguide(2).id="if key e and agent is on location x1 y1 then trigger outcomes"
triggerguide(2).x="location x"
triggerguide(2).y="location y"
triggerguide(2).id1="agent id"

outcomeguide(0).id="change level tile"
outcomeguide(0).x="location x"
outcomeguide(0).y="location y"
outcomeguide(0).val1="tile kind"
outcomeguide(0).bool1="wall"
outcomeguide(0).bool2="visionblock"
outcomeguide(1).id="reactivate current action"
outcomeguide(2).id="activate/deactivate another action"
outcomeguide(2).bool1="on/off"
outcomeguide(3).id="set timer for another actions trigger"
outcomeguide(3).id1="action id"
outcomeguide(3).id2="trigger id"
outcomeguide(3).timev="time in seconds from now"
outcomeguide(5).id="show text box"
outcomeguide(5).id1="textbox id"*/

class trigger{
    public:
    int32_t id = 0;

    int32_t id1 = 0;
    int32_t id2 = 0;
    int32_t x = 0;
    int32_t y = 0;
    double timev = 0;
    int32_t val1 = 0;
    int32_t val2 = 0;
    bool bool1 = false;
    bool bool2 = false;
};

class outcome{
    public:
    int32_t id = 0;
    
    int32_t id1 = 0;
    int32_t id2 = 0;
    int32_t x = 0;
    int32_t y = 0;
    double timev = 0;
    int32_t val1 = 0;
    int32_t val2 = 0;
    bool bool1 = false;
    bool bool2 = false;
};

class action {
    public:
    char * namestr = strdup(temp1);
    vector<trigger> triggers;
    vector<outcome> outcomes;
    bool active = false;




    void check(vector<action> &actions, vector<agent> &agents, map &curlevel, userinterface &ui ) {
        if (active==true) {
            for (uint32_t i = 0; i < triggers.size(); i++) {
                switch (triggers.at(i).id) {
                case 0: //If agent( id1 ) is on location x1 y1 then trigger outcomes
                    if (round(agents.at(triggers.at(i).id1).x)==triggers.at(i).x && round(agents.at(triggers.at(i).id1).y)==triggers.at(i).y) { perform(actions,agents,curlevel,ui);}
                    break;
                case 1: //if time is reached then trigger outcomes
                    if (cTimer()>triggers.at(i).timev) { perform(actions,agents,curlevel,ui);}
                    break;
                case 2: //if key"e" and If agent( id1 ) is on location x1 y1 then trigger outcomes
                    if (*keyboard.k=='e' && round(agents.at(triggers.at(i).id1).x)==triggers.at(i).x && round(agents.at(triggers.at(i).id1).y)==triggers.at(i).y) { *keyboard.k=' ';perform(actions,agents,curlevel,ui);}
                    break;
                }
            }
        }
    }

    void perform(vector<action> &actions,vector<agent> &agents, map &curlevel,userinterface &ui) {
        active=false;
        for (uint32_t i = 0; i < outcomes.size(); i++) {
            switch (outcomes.at(i).id) {
            case 0: //change level tile
                curlevel.tiles2.at(outcomes.at(i).x).at(outcomes.at(i).y).grfkind=outcomes.at(i).val1;
                curlevel.tiles.at(outcomes.at(i).x).at(outcomes.at(i).y).wall=outcomes.at(i).bool1;
                curlevel.tiles.at(outcomes.at(i).x).at(outcomes.at(i).y).visionblock=outcomes.at(i).bool2;
                break;
            case 1: //reactivate
                active=true;
                break;
            case 2: //activate/deactivate another action
                actions.at(outcomes.at(i).id1).active=outcomes.at(i).bool1;
                break;
            case 3: //set timer for another actions trigger
                actions.at(outcomes.at(i).id1).triggers.at(outcomes.at(i).id2).timev=cTimer()+outcomes.at(i).timev;
                break;
            case 4: //show story message
                
                break;
            case 5: //show press e to use
                ui.textboxes.at(outcomes.at(i).id1).active=true;
                break;
            }
        }
    }


};

