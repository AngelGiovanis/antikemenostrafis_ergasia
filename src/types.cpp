#include "../include/types.h"

#include <vector>
#include <string>

//parameters class functions intrepretatinos

void parameters::print_debug() const{
    cout << "Parameters Debug Info:" << endl;
    cout << "  seed: " << seed << endl;
    cout << "  world_width: " << world_width << endl;
    cout << "  world_height: " << world_height << endl;
    cout << "  num_moving_cars: " << num_moving_cars << endl;
    cout << "  num_moving_bikes: " << num_moving_bikes << endl;
    cout << "  num_parked_cars: " << num_parked_cars << endl;
    cout << "  num_stop_signs: " << num_stop_signs << endl;
    cout << "  num_traffic_lights: " << num_traffic_lights << endl;
    cout << "  max_simulation_ticks: " << max_simulation_ticks << endl;
    cout << "  min_confidence_threshold: " << min_confidence_threshold << endl;
}


void parameters::extract_info(char ** argv,int argc){
    for(int i = 1; i < argc; i+=2){
        if(string(argv[i]) == "--help"){
            print_help();
        }
        if(string(argv[i]) == "--seed"){
            seed = atoi(argv[i + 1]);
        }
        if(string(argv[i]) == "--dimX"){
            world_width = atoi(argv[i + 1]);
        }
        if(string(argv[i]) == "--dimY"){
            world_height = atoi(argv[i + 1]);
        }
        if(string(argv[i]) == "--numMovingCars"){
            num_moving_cars = atoi(argv[i + 1]);
        }
        if(string(argv[i]) == "--numMovingBikes"){
            num_moving_bikes = atoi(argv[i + 1]);
        }
        if(string(argv[i]) == "--numParkedCars"){
            num_parked_cars = atoi(argv[i + 1]);
        }
        if(string(argv[i]) == "--numStopSigns"){
            num_stop_signs = atoi(argv[i + 1]);
        }
        if(string(argv[i]) == "--numTrafficLights"){
            num_traffic_lights = atoi(argv[i + 1]);
        }
        if(string(argv[i]) == "--simulationTicks"){
            max_simulation_ticks = atoi(argv[i + 1]);
        }
        if(string(argv[i]) == "--minConfidenceThreshold"){
            min_confidence_threshold = atoi(argv[i + 1]);
        }

        if(string(argv[i]) == "--gps"){
            //TODO edw prepei na dw pws tha kanw extract ploiroforia 
        }

    }
}

parameters::parameters()
    :seed(time(0)),world_width(40),world_height(40),num_moving_cars(3),num_moving_bikes(4),num_parked_cars(5),num_stop_signs(2),num_traffic_lights(2),max_simulation_ticks(100),min_confidence_threshold(40)
    {
        srand(seed);
    }
    //TODO i need to find a function that tells the current time for seed 


void parameters::print_help() const{
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

grid_world::~grid_world(){
    for(int i = 0; i< height; i++){
        delete[] map[i];
    }
    delete[] map;

}

grid_world::grid_world(parameters parametroi)
    :height(parametroi.world_height),width(parametroi.world_width)
    {

    }
    //works because all the parameters are public haha to get fiunction

void grid_world::create_map(){
    map = new int*[height];
    for(int i = 0; i < height; i ++){ //didnt use vector because size is static
        map[i] = new int[width]();
    }
}


//gia traffic_light


trafic_light::trafic_light()
    :katastasi("RED"),fanari_ticks(0)
    {

    }

void trafic_light::change_the_state(){ 
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

//self driving car 
void self_driving_car::accelerate(){
    if(speed == "STOPPED"){
        speed = "HALF_SPEED";
    }
    else if(speed == "HALF_SPEED"){
        speed = "FULL_SPEED";
    }
}

//meiwse taxitita
void self_driving_car::decelerate(){
    if(speed == "HALF_SPEED"){
        speed = "STOPPED";
    }
    else if(speed == "FULL_SPEED"){
        speed = "HALF_SPEED";
    }
}
