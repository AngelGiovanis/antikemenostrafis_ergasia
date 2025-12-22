#include <stdio.h>
#include  "../include/types.h"
#include <chrono>
#include <thread>





int main(int argc, char ** argv ){
    if (argc < 3){
        cout<<"program should be called as ./program name target_x target_y"<<endl;
        return 1;
    }

    parameters p; //constructor arxikopoiei times 

    
    
    p.extract_info(argv,argc); //xristis tis allazei
    srand(p.get_seed()); //thetei to randomness 
    
    
    grid_world plegma(p); //arxikopoiei to plegma

    self_driving_car amaksi(p,&plegma); //intialize self driving car

    world kosmos(&p,&plegma); //dimiourgei klasi kosmos poy tha diaxeirizetai antikeimena 


    // plegma.debug();
    
    kosmos.update(plegma,amaksi); 
    plegma.debug(); //arxiko print


    while(kosmos.get_ticks() < p.get_ticks() && !kosmos.is_finished()){

        amaksi.print_direction();
        kosmos.update(plegma,amaksi); //kanei update sto grid tin current thesi twn pragmatwn 
        

        
        plegma.debug(); //printarei kosmo 
        std::this_thread::sleep_for(std::chrono::milliseconds(1500)); //to check the implementation
    }

    cout<<p.get_ticks()<<endl;
    return 0;
}