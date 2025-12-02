#include <stdio.h>
#include  "../include/types.h"


int main(int argc, char ** argv ){
    if (argc < 3){
        cout<<"program should be called as ./program name target_x target_y"<<endl;
        return 1;
    }

    parameters p; //constructor arxikopoiei times 
    p.extract_info(argv,argc); //xristis tis allazei 

    world kosmos;

    while(kosmos.current_ticks < p.max_simulation_ticks && !kosmos.finished){
        kosmos.update();
    }

    //?while loop pou tha elegxei an current_ticks<max_ticks kai not_finished variable pou koitaei an self_driving_car exei kanei tin diadromi toy

    return 0;
}