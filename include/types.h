#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

class position{
    private:
        int x;
        int y;
    public:
        int get_x() const;
        int get_y() const;
        position(const int &grammes,const int &stilles);
        position();
        void set_positions(int x1, int y1);
};


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
    //TODO i need to see how i can interpret the cords x and y starting and ending (vector or queue)
    vector <position> gps_targets;
    
    void extract_gps_targets( char ** argv, int index_of_gps_flag, int argc);
    
    void print_help() const ;
    
    void print_debug() const;
    void extract_info(char ** argv,int argc);
    
    parameters(); //we need two constructors one that is if they only gave the gps and one for if they gave other thigns also
};

class grid_world{
    private:
    int height;
    int width;
    char ** map; //use it to access the array 
    public:
    grid_world(parameters parametroi);
    
    void create_map();
    
    void change_char(int x, int y, char c);
    
    void debug() const;
    
    ~grid_world();
};

/*
Το αυτόνομο όχημα τοποθετείται σε ένα κελί και έχει κατεύθυνση (direction)
και ταχύτητα (speed). Οι καταστάσεις ταχύτητας είναι STOPPED (σταματημένο),
HALF_SPEED (το ήμισυ της πλήρους ταχύτητας) ή FULL_SPEED (2 θέσεις ανά
tick).
*/

class self_driving_car{
    private:
    // sensors sensores;
    // navigation_system ploigisi;
    string speed; 
    public:
    position thesi;
    self_driving_car(parameters p);
    void accelerate();
    void decelerate();
    void turn();
    
    
    
};

class navigation_system{
    public:
    private:
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
    void get_thesi(int &x, int &y) const;
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
    trafic_light();
    ~trafic_light();
    
};



class moving_object:private object{
    private:
    string speed;
    //? pws skata tha kanw interpret to direction
    public:
    
};

class world{
    public:
        bool finished;
        int current_ticks;
        void update(grid_world &plegma, self_driving_car &amaksi);
        world(); //initializes world,puts all characters inside 

};



#endif