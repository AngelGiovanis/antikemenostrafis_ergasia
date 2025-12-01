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
        int min_confidence_threshold;
        //TODO i need to see how i can interpret the cords x and y starting and ending 
    void print_help();

    void extract_info(char * argv);

    parameters(); //we need two constructors one that is if they only gave the gps and one for if they gave other thigns also
};

class grid_world{
    private:
        int height;
        int width;
        int * map;
    public:
        grid_world(parameters parametroi);

        int * create_map(){

        }

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

        void change_the_state();

};

class moving_object:private object{
    private:

    public:
};




#endif