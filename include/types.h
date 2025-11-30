#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

class parameters{
    public:
        int seed;
        int world_width;
        int world_height;
        int num_moving_cars;
        int num_moving_bikes;
        int num_parked_cars;
        int num_stop_signs;
        int num_traffic_lights;
        int max_simulation_ticks;
        //TODO i need to see how i can interpret the cords x and y starting and ending 
    void print_help(){
        // cout << "Self-Driving Car Simulation" << endl;
        // cout << "Usage:" << endl;
        // cout << "  --seed <n>                Random seed (default: current time)" << endl; //this. thing goes int hte .cpp file
        // cout << "  --dimX <n>                World width (default: 40)" << endl;
        // cout << "  --dimY <n>                World height (default: 40)" << endl;
        // cout << "  --numMovingCars <n>       Number of moving cars (default: 3)" << endl;
        // cout << "  --numMovingBikes <n>      Number of moving bikes (default: 4)" << endl;
        // cout << "  --numParkedCars <n>       Number of parked cars (default: 5)" << endl;
        // cout << "  --numStopSigns <n>        Number of stop signs (default: 2)" << endl;
        // cout << "  --numTrafficLights <n>    Number of traffic lights (default: 2)" << endl;
        // cout << "  --simulationTicks <n>     Maximum simulation ticks (default: 100)" << endl;
        // cout << "  --minConfidenceThreshold <n>  Minimum confidence cutoff (default: 40)" << endl;
        // cout << "  --gps <x1> <y1> [x2 y2 ...]  GPS target coordinates (required)" << endl;
        // cout << "  --help                    Show this help message" << endl << endl;
        // cout << "Example usage:" << endl;
        // cout << "  ./oopp_proj_2025 --seed 12 --dimY 50 --gps 10 20 32 15" << endl;
    }

    parameters(); //we need two constructors one that is if they only gave the gps and one for if they gave other thigns also
    parameters(char * argv);
};

class grid_world{
    private:
        int grammes;
        int stiles;
    public:

};


class self_driving_car{
    private:
        sensors sensoras;
    public:
};

class navigation_system{
    public:
    private:
};

class world_object{
    public:
    private:
};

class position{
    private:
        int x;
        int y;
    public:
        

};

class sensors{
    private:
    public:
};


class object{
    protected:
        string id;
        char glyph;
        position thesi;
    public:
        void get_id(string &tautotita) const;
        void get_glyph(char &xaraktiras) const;
};

class traffic_sign:private object{
    private:
        string message;
    public:
        void get_message(string &minima);
};

class trafic_light:private object{ //TODO den mou aresei auti i ilopoiisi
    private:
        string katastasi;
        int fanari_ticks;
    public:

        void change_the_state(){ //skata ksexnaw oti den ginontai edw oi ilopoiiseis
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

};

class moving_object:private object{
    private:

    public:
};




#endif