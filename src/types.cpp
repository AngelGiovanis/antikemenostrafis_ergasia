#include "../include/types.h"

#include <vector>

//parameters class functions intrepretatinos

parameters::parameters()
    :seed(),world_width(40),world_height(40),num_moving_cars(3),num_moving_bikes(4),num_parked_cars(5),num_stop_signs(2),num_traffic_lights(2),max_simulation_ticks(100),min_confidence_threshold(40)
    {

    }
    //TODO i need to find a function that tells the current time for seed 


void parameters::print_help(){
    cout << "Self-Driving Car Simulation" << endl;
    cout << "Usage:" << endl;
    cout << "  --seed <n>                Random seed (default: current time)" << endl; //this. thing goes int hte .cpp file
    cout << "  --dimX <n>                World width (default: 40)" << endl;
    cout << "  --dimY <n>                World height (default: 40)" << endl;
    cout << "  --numMovingCars <n>       Number of moving cars (default: 3)" << endl;
    cout << "  --numMovingBikes <n>      Number of moving bikes (default: 4)" << endl;
    cout << "  --numParkedCars <n>       Number of parked cars (default: 5)" << endl;
    cout << "  --numStopSigns <n>        Number of stop signs (default: 2)" << endl;
    cout << "  --numTrafficLights <n>    Number of traffic lights (default: 2)" << endl;
    cout << "  --simulationTicks <n>     Maximum simulation ticks (default: 100)" << endl;
    cout << "  --minConfidenceThreshold <n>  Minimum confidence cutoff (default: 40)" << endl;
    cout << "  --gps <x1> <y1> [x2 y2 ...]  GPS target coordinates (required)" << endl;
    cout << "  --help                    Show this help message" << endl << endl;
    cout << "Example usage:" << endl;
    cout << "  ./oopp_proj_2025 --seed 12 --dimY 50 --gps 10 20 32 15" << endl;
}

//gia gird_world
grid_world::grid_world(parameters parametroi)
    :height(parametroi.world_height),width(parametroi.world_width)
    {

    }
    //works because all the parameters are public haha to get fiunction

//gia traffic_light

void trafic_light::change_the_state(){ //skata ksexnaw oti den ginontai edw oi ilopoiiseis
    if(fanari_ticks < 4){
        katastasi = "RED";
    }
    else if(fanari_ticks > 4 && fanari_ticks < 12){
        katastasi = "GREEN";
    }
    else if(fanari_ticks < 14){
        katastasi = "YELLOW";
    }
    else{
        fanari_ticks = 0;
        katastasi = "RED";
    }
}