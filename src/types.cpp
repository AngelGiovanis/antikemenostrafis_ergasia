#include "../include/types.h"

//self driving car 
void self_driving_car::accelerate(){
    if(speed == "STOPPED"){
        speed = "HALF_SPEED";
    }
    else if(speed == "HALF_SPEED"){
        speed = "FULL_SPEED";
    }
}


void self_driving_car::decelerate(){
    if(speed == "HALF_SPEED"){
        speed = "STOPPED";
    }
    else if(speed == "FULL_SPEED"){
        speed = "HALF_SPEED";
    }
}

self_driving_car::self_driving_car(parameters p){
    thesi.set_positions(rand() % p.get_world_height(),rand() % p.get_world_width());
}



void parameters::extract_gps_targets( char ** argv, int index_of_gps_flag, int argc){
    index_of_gps_flag++;
    while(index_of_gps_flag < argc){
        gps_targets.push_back(position(atoi(argv[index_of_gps_flag]),atoi(argv[index_of_gps_flag + 1])));
        index_of_gps_flag+=2;
    }
}
//parameters class functions intrepretatinos





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
            this->extract_gps_targets(argv,i,argc);
        }
        
    }
}

parameters::parameters()
:seed(time(0)),world_width(40),world_height(40),num_moving_cars(3),num_moving_bikes(4),num_parked_cars(5),num_stop_signs(2),num_traffic_lights(2),max_simulation_ticks(100),min_confidence_threshold(40)
{
}


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

int parameters::get_seed() const{
    return seed;
}

int parameters::get_world_height() const{
    return world_height;
}
        
int parameters::get_world_width() const{
    return world_width;
}

int parameters::get_moving_bikes() const{
    return num_moving_bikes;
}

int parameters::get_moving_cars() const{
    return num_moving_cars;
}

int parameters::get_ticks() const {
    return max_simulation_ticks;
}

int parameters::get_parked_cars() const{
    return num_parked_cars;
}

int parameters::get_traffic_lights() const{
    return num_traffic_lights;
}


//gia gird_world

grid_world::~grid_world(){
    for(int i = 0; i< height; i++){
        delete[] map[i];
    }
    delete[] map;
    
}

grid_world::grid_world(const parameters &parametroi)
    :height(parametroi.get_world_height()),width(parametroi.get_world_width())
    {
        create_map();
    }

void grid_world::debug() const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << map[i][j] << ' ';
        }
        cout << endl;
    }
}

void grid_world::create_map(){
    map = new char*[height];
    for(int i = 0; i < height; i ++){ //didnt use vector because size is static
        map[i] = new char[width]();
        for(int j = 0; j < width; j++){
            map[i][j] = '.'; //arxikopoiei tis theseis me teleies
        }
    }
}

void grid_world::change_char(int x,int y, char c){
    map[x][y] = c;
}


//gia traffic_light


trafic_light::trafic_light(const parameters &p)
    :katastasi("RED"),fanari_ticks(0)
{
    thesi.set_positions(rand() % p.get_world_height(),rand() % p.get_world_width());
    update();
}

void trafic_light::update(){ 
    if(fanari_ticks < 4){
        katastasi = "RED";
        glyph = 'R';
    }
    else if(fanari_ticks > 4 && fanari_ticks < 12){
        katastasi = "GREEN";
        glyph = 'G';
    }
    else if(fanari_ticks < 14){
        katastasi = "YELLOW";
        glyph = 'Y';
    }
    else{
        fanari_ticks = 0;
        katastasi = "RED";
        glyph = 'R';
    }
    fanari_ticks++;
}


//position
position::position(const int &grammes,const int &stilles)
: x(grammes),y(stilles)
    {

    }

position::position()
    :x(0),y(0){}

int position::get_x() const{
    return x;
}

int position::get_y() const{
    return y;
}

void position::set_positions(int x1, int y1){
    x = x1;
    y = y1;
}


//gia world
void world::initialize_moving_objects(parameters * params){

    for(int i = 0; i < params->get_moving_cars(); i++){
        moving_objects.push_back(new car(*params));
    }

    for(int i = 0; i < params->get_moving_bikes(); i++){
        moving_objects.push_back(new bike(*params));
    }
}

void world::initialize_static_objects(parameters * params){

    for(int i = 0; i < params->get_traffic_lights(); i++){
        static_objects.push_back(new trafic_light(*params));
    }
}


world::world(parameters * params,grid_world * plegma)
    :finished(false),current_ticks(0),p(params),xartis(plegma)
    {
        initialize_moving_objects(params);
        initialize_static_objects(params);
    }

void world::update(grid_world &plegma,self_driving_car &amaksi){
    current_ticks++;
    plegma.change_char(amaksi.thesi.get_x(),amaksi.thesi.get_y(),'@');
    for(auto obj: moving_objects){ //to chat me voitithise me to na kanw loop through objects se ena vector
        plegma.change_char(obj->thesi.get_x(), obj->thesi.get_y(), obj->glyph);
    }

    for(auto obj: static_objects){
        if(obj->glyph == 'R' || obj->glyph == 'Y' || obj->glyph == 'G'){
            obj->update();
        }
        plegma.change_char(obj->thesi.get_x(), obj->thesi.get_y(), obj->glyph);
    }
}

int world::get_ticks(){
    return current_ticks;
}

bool world::is_finished(){
    return finished;
}

world::~world(){
}


//for object
void object::update(){

}


//for car

int car::car_count = 1;


car::car(const parameters &p){
    id = "car"+ to_string(car_count++);
    glyph = 'C';
    speed = "SLOW";
    thesi.set_positions(rand() % p.get_world_height(),rand() % p.get_world_width());
}
//for bike

bike::bike(const parameters &p){
    id = "bike" + to_string(bike_count);
    glyph = 'B';
    speed = "SLOW";
    thesi.set_positions(rand() % p.get_world_height(),rand() % p.get_world_width());

}

int bike::bike_count = 1;