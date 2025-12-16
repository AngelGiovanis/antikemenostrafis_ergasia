#include "../include/types.h"


//parameters class functions intrepretatinos

void parameters::extract_gps_targets( char ** argv, int index_of_gps_flag, int argc){
    index_of_gps_flag++;
    while(index_of_gps_flag < argc){
        gps_targets.push_back(position(atoi(argv[index_of_gps_flag]),atoi(argv[index_of_gps_flag + 1])));
        index_of_gps_flag+=2;
    }
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

int parameters::get_traffic_signs() const{
    return num_stop_signs;
}


//gia gird_world

grid_world::~grid_world(){
    for(int i = 0; i < height; i++){
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
            if(map[i][j]){
                cout << map[i][j]->glyph << ' ';
            }
            else{
                cout<<'.'<<' ';
            }
        }
        cout << endl;
    }
}

void grid_world::create_map(){
    height++;
    width++;
    map = new object **[height];
    for(int i = 0; i < height; i ++){ //didnt use vector because size is static
        map[i] = new object*[width]();
        for(int j = 0; j < width; j++){
            map[i][j] = nullptr; //arxikopoiei tis theseis me teleies
            if(j == 0 || i == 0 || j == width - 1 || i == width -1){
                map[i][j] = new wall();
            }
        }
    }
}

void grid_world::change_char(int x,int y, object * obj){
    map[x][y] = obj;
}

object *** grid_world::return_map_pointer(){
    return map;
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

void position::set_positions(const int x1,const int y1){
    x = x1;
    y = y1;
}

void position::set_y(const int y1){
    y = y1;
}
void position::set_x(const int x1){
    x = x1;
}



//gia world
void world::initialize_moving_objects(parameters * params){
    
    for(int i = 0; i < params->get_moving_cars(); i++){
        moving_objects.push_back(new car(*params,xartis));
    }
    
    for(int i = 0; i < params->get_moving_bikes(); i++){
        moving_objects.push_back(new bike(*params,xartis));
    }
}

void world::initialize_static_objects(parameters * params){
    
    for(int i = 0; i < params->get_traffic_lights(); i++){
        static_objects.push_back(new trafic_light(*params ));
    }
    for(int i = 0; i < params->get_parked_cars(); i++){
        static_objects.push_back(new parked_car(*params));
    }
    for(int i = 0;i < params->get_traffic_signs(); i++){
        static_objects.push_back(new traffic_sign(*params));
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
    plegma.change_char(amaksi.thesi.get_x(),amaksi.thesi.get_y(),&amaksi);
    for(auto obj: moving_objects){ //to chat me voitithise me to na kanw loop through objects se ena vector
        // plegma.change_char(obj->thesi.get_x(), obj->thesi.get_y(), obj->glyph);
        obj->move();
    }
    
    for(auto obj: static_objects){
        if(obj->glyph == 'R' || obj->glyph == 'Y' || obj->glyph == 'G'){
            obj->update();
        }
        plegma.change_char(obj->thesi.get_x(), obj->thesi.get_y(), obj);
    }
}

int world::get_ticks(){
    return current_ticks;
}

bool world::is_finished(){
    return finished;
}

world::~world(){
    for(auto obj: moving_objects){
        delete obj;
    }
    moving_objects.clear();
    
    
    for (auto obj : static_objects) {
        delete obj;
    }
    
    static_objects.clear();
}


//for object
void object::update(){
}

//for waaaalllllllllaaalallalalala
wall::wall(){
    glyph = 'X';
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

void self_driving_car::decelerate(){
    if(speed == "HALF_SPEED"){
        speed = "STOPPED";
    }
    else if(speed == "FULL_SPEED"){
        speed = "HALF_SPEED";
    }
}

self_driving_car::self_driving_car(parameters p){
    thesi.set_positions(rand() % (p.get_world_height()- 2),rand() % (p.get_world_width() - 2));
    glyph = '@';
}

//for sensors 
sensors sensors::extract_info(){
}


lidar_sensor::lidar_sensor(object *** xartis , position * posi , string tax , string conf){
    map = xartis;
    thesi_amaksiou = posi;
    speed = tax;
    confidence = conf;
}

sensors lidar_sensor::extract_info(){
    char c;
    for(int i = thesi_amaksiou->get_x() - 4; i < thesi_amaksiou->get_x() + 4; i++){
        for(int j = thesi_amaksiou->get_y() - 4; j < thesi_amaksiou->get_y() + 4; j++){
            if (i >= 0 && i < 40 && j >= 0 && j < 40 && map[i][j] && map[i][j]->glyph != 'X') { //gia na min faw segfault gia na min kanw access nullptr kai min kanw access edge X :p
                if(map[i][j] && map[i][j]->glyph != 'X'){
                    c = map[i][j]->glyph;
                    if(c == 'C' || c == 'B'){
                        objects.push_back('M');
                    }
                    else{
                        objects.push_back('S');
                    }
                    positions.push_back((i-thesi_amaksiou->get_x())+(j-thesi_amaksiou->get_y())); //manhattan distance 
                    //TODO na kanw implement to accuracy
                }
            }
        }
    }
}

//radar sensor love 

radar_sensor::radar_sensor(object *** xartis , position * posi , string tax , string conf){
    map = xartis;
    thesi_amaksiou = posi;
    speed = tax;
    confidence = conf;
} //TODO tha to allaksw kai tha valw ton idio constructor giati kanei tin idia douleia 

sensors radar_sensor::extract_info(){
    moving_object* pointer;
    int i = thesi_amaksiou->get_x();
    for(int j = thesi_amaksiou->get_y() + 1; i < thesi_amaksiou->get_x() + 4; i++){
        if (i >= 0 && i < 40 && j >= 0 && j < 40 && map[i][j] && map[i][j]->glyph != 'X') { //gia na min faw segfault gia na min kanw access nullptr kai min kanw access edge X :p
            if(map[i][j] && map[i][j]->glyph != 'X' && (map[i][j]->glyph == 'B' || map[i][j]->glyph == 'C')){
                positions.push_back((i-thesi_amaksiou->get_x())+(j-thesi_amaksiou->get_y())); //manhattan distance 
                pointer = static_cast<moving_object*>(map[i][j]);
                object_speed.push_back(pointer->get_speed());
                //TODO katefthinsi
                //TODO vevaiotita
            }
        }
    }
}

//for moving_object
moving_object::moving_object(grid_world * grid){
    plegma = grid;
    current_ticks = 0;
}

void moving_object::move(){
}

string moving_object::get_speed(){
    return speed;
}


//gia traffic_light

trafic_light::trafic_light(const parameters &p)
    :katastasi("RED"),fanari_ticks(0)
{
    thesi.set_positions(rand() % (p.get_world_height()- 2),rand() % (p.get_world_width() - 2)); //-2 ensures the object is not initialized at the edges
    update();
}

void trafic_light::update(){ 
    if(fanari_ticks < 4){
        katastasi = "RED";
        glyph = 'R';
    }
    else if(fanari_ticks < 12){
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

//for parked_car
parked_car::parked_car(const parameters &p){
    id = "parked_car" + to_string(parked_car_count++);
    glyph = 'P';
    thesi.set_positions(rand() % (p.get_world_height()- 2),rand() % (p.get_world_width() - 2));
}

int parked_car::parked_car_count = 1;

//for traffic lights 
traffic_sign::traffic_sign(const parameters &p){
    id = "traffic_sign" + to_string(traffic_signs_count++);
    xaraktirismos = "STOP";
    glyph = 'S';
    thesi.set_positions(rand() % (p.get_world_height()- 2),rand() % (p.get_world_width() - 2));
}

int traffic_sign::traffic_signs_count = 1;

//for car

int car::car_count = 1;


car::car(const parameters &p , grid_world * xartis)
        :moving_object(xartis)
    {
        speed = "FULL_SPEED";
        id = "car"+ to_string(car_count++);
        glyph = 'C';
        thesi.set_positions(rand() % (p.get_world_height()- 2),rand() % (p.get_world_width() - 2));
    }

void car::move(){
    if(thesi.get_x() - 2 > 0 ){
        plegma->change_char(thesi.get_x(),thesi.get_y(),nullptr); // kane to current teleia
        
        thesi.set_x(thesi.get_x() - 2);

        //kane to apo panw teleia
        plegma->change_char(thesi.get_x(),thesi.get_y(),this);
    }
    else{
        //TODO simainei oti einai sto edge ara prepei na allaksei direction
    }
}


//for bike
int bike::bike_count = 1;

bike::bike(const parameters &p,grid_world* grid)
        :moving_object(grid){
            id = "bike" + to_string(bike_count);
            glyph = 'B';
            thesi.set_positions(rand() % (p.get_world_height()- 2),rand() % (p.get_world_width() - 2));
            speed = "HALF_SPEED";
        }

void bike::move(){
    if(thesi.get_x() - 1 != 0){
        plegma->change_char(thesi.get_x(),thesi.get_y(),nullptr); // kane to current teleia
        
        thesi.set_x(thesi.get_x() - 1);

        //kane to apo panw teleia
        plegma->change_char(thesi.get_x(),thesi.get_y(),this);
    }
    else{

    }
}

