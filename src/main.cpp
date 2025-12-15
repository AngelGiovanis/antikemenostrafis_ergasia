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
    self_driving_car amaksi(p); //intialize self driving car


    grid_world plegma(p); //arxikopoiei to plegma

    world kosmos(&p,&plegma); //dimiourgei klasi kosmos poy tha diaxeirizetai antikeimena 


    // plegma.debug();
    
    kosmos.update(plegma,amaksi); //arxiko print
    //plegma.debug(); idio me kosmos.update nomizw


    while(kosmos.get_ticks() < p.get_ticks() && !kosmos.is_finished()){

        kosmos.update(plegma,amaksi); //printarei kosmo 
        
        cout<<kosmos.get_ticks()<<endl; //printarei current tick 
        
        plegma.debug();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //to check the implementation
    }

    cout<<p.get_ticks()<<endl;
    //?while loop pou tha elegxei an current_ticks<max_ticks kai not_finished variable pou koitaei an self_driving_car exei kanei tin diadromi toy

    return 0;
}