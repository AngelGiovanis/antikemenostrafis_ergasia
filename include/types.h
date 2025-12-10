#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>

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
    private:
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
        vector <position> gps_targets;

    public:
        int get_seed() const;

        int get_world_height() const;
        
        int get_world_width() const;

        void print_help() const ;
            
        void extract_info(char ** argv,int argc);

        int get_moving_cars() const;

        int get_moving_bikes() const;

        int get_ticks() const;

        int get_parked_cars() const;

        int get_traffic_lights() const;

        parameters(); //we need two constructors one that is if they only gave the gps and one for if they gave other thigns also
        void extract_gps_targets( char ** argv, int index_of_gps_flag, int argc);
    };
    

class grid_world{
    private:
        int height;
        int width;
        char ** map; //use it to access the array 

    public:
        grid_world(const parameters &parametroi);
        
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
    public:
        char glyph;
        position thesi;
        virtual void update();
};

class moving_object:public object{
    protected:
        string speed;
    public:

};

class car: public moving_object{
    private:
        static int car_count;
    public:
        car(const parameters &p);
};




class bike: public moving_object{
    private:
        static int bike_count;
    public:
        bike(const parameters &p);
};




class trafic_light:public object{ //TODO den mou aresei auti i ilopoiisi
    private:
        string katastasi;
        int fanari_ticks;
    public:
        void update();
        trafic_light(const parameters &p);
        ~trafic_light();

    
};

class world{
    private:
        bool finished;
        int current_ticks;

        parameters * p;

        grid_world * xartis;

        
    public:
        vector<moving_object*> moving_objects;

        vector<object*> static_objects;
        bool is_finished();
        int get_ticks();
        void update(grid_world &plegma, self_driving_car &amaksi);

        void initialize_moving_objects(parameters * params);
        void initialize_static_objects(parameters * params);

        world(parameters * params,grid_world * plegma); //initializes world,puts all characters inside 

        ~world();
};


#endif