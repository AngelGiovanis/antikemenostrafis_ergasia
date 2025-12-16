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
        void set_y(const int y1);
        void set_x(const int x1);
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

        int get_traffic_signs() const;

        parameters(); //we need two constructors one that is if they only gave the gps and one for if they gave other thigns also
        void extract_gps_targets( char ** argv, int index_of_gps_flag, int argc);
    };
        
class object{
    protected:
        string id;
    public:
        char glyph;
        position thesi;
        virtual void update();
};

class navigation_system{
    private:
        vector <position> gps_targets;

    public:
        void make_decision();
    
};


//TODO SENSORES 
/*•2.2.1 Αισθητήρας Lidar (Lidar Sensor) Εμβέλεια: 9 κελιά
• Οπτικό πεδίο: Ένα τετράγωνο 81 κελιών, με κεντρικό κελί στο όχημα (δηλαδή
όραση «360 μοιρών» 9x9 κελιών)
• Ανιχνεύει: Όλα τα αντικείμενα (στατικά και κινούμενα), όχι όμως χρώμα φαναριών ή κείμενο πινακίδας
• Επιστρέφει: Απόσταση, κατηγορία αντικειμένου, βεβαιότητα
• Ακρίβεια: Εξαιρετική για απόσταση, μέτρια για κατηγοριοποίηση
2.2.2 Αισθητήρας ραντάρ (Radar Sensor)
• Εμβέλεια: 12 κελιά
• Οπτικό πεδίο: 12 κελιά ευθεία μπροστά
• Ανιχνεύει: Μόνο κινούμενα αντικείμενα
• Επιστρέφει: Απόσταση, ταχύτητα, κατεύθυνση κίνησης, βεβαιότητα
• Ακρίβεια: Υψηλή για απόσταση και για κατηγοριοποίηση*/

class sensors{
    protected:
        object *** map;
        position * thesi_amaksiou;
        string speed;
        string confidence; //maybe??
    public:
        virtual sensors extract_info();
};

class lidar_sensor : public sensors{
    private:
        vector<position*> positions;
        vector<char> objects;
    public:
        lidar_sensor(object *** map,position * pos,string tax,string conf);
        sensors extract_info();
};

class radar_sensor : public sensors{
    private:

    public:

};

class camera_sensor : public sensors{
    private:

    public:
};


class grid_world{
    private:
        int height;
        int width;
        object *** map; //use it to access the array map[i][j] = object*

    public:
        grid_world(const parameters &parametroi);
        
        void create_map();
        
        void change_char(int x, int y, object * obj);
        
        void debug() const;

        object *** return_map_pointer();
        
        ~grid_world();
};



class self_driving_car : public object {
    private:
        // sensors sensores; //auto den exw idea pws tha to kanw implement
        // navigation_system ploigisi;
        string speed; 
    public:
        self_driving_car(parameters p);
        void accelerate();
        void decelerate();
        void turn();
};


class wall : public object {
    public:
        wall();
};

class moving_object:public object{ //TODO i need to think for the implementation of direction
    protected:
        grid_world *plegma;
        int current_ticks;
    public:
        virtual void move();
        moving_object(grid_world* grid);


};

class car: public moving_object{
    private:
        static int car_count;
    public:
        car(const parameters &p,grid_world *xartis);
        void move();
};

class bike: public moving_object{
    private:
        static int bike_count;
    public:
        bike(const parameters &p,grid_world* xartis);
        void move();
};

class parked_car : public object{
    private:
        static int parked_car_count;
    public:
        parked_car(const parameters &p);
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

class traffic_sign: public object{
    private:
        static int traffic_signs_count;
        string xaraktirismos;
    public:
        traffic_sign(const parameters &p);
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