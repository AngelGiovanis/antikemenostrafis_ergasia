#include <stdio.h>
#include  "../include/types.h"


int main(int argc, char ** argv ){
    if (argc < 3){
        cout<<"program should be called as ./program name target_x target_y"<<endl;
        return 1;
    }

    parameters p; //constructor arxikopoiei times 

    
    
    p.extract_info(argv,argc); //xristis tis allazei
    srand(p.get_seed());
    self_driving_car amaksi(p);


    grid_world plegma(p);

    world kosmos(&p,&plegma);


    // plegma.debug();
    
    kosmos.update(plegma,amaksi); //arxiko print
    plegma.debug();


    while(kosmos.get_ticks() < p.get_ticks() && !kosmos.is_finished()){

        kosmos.update(plegma,amaksi);
        
        cout<<"---------------AAAAAAHhHHHHHHHHH-------------"<<endl;
        
        plegma.debug();
    }

    cout<<p.get_ticks();
    //?while loop pou tha elegxei an current_ticks<max_ticks kai not_finished variable pou koitaei an self_driving_car exei kanei tin diadromi toy

    return 0;
}