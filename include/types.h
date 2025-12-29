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

struct direction {
    int dx;
    int dy;
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
        string get_id();
        virtual void update();
        virtual bool is_moving();

};

class navigation_system{
    private:
        vector <position> gps_targets;

    public:
        void make_decision();
    
};
struct sensor_reading {
    string id; //taytotita
    position pos; //position
    int distance; //distance akraio e
    string type; //type car or bike or whatever
    int speed; //speed 
    direction dir; //direction
    string sign_text;
    char traffic_light;
    float confidence; //confidence
};

class sensors{
    protected:
        object *** map;
        position * thesi_amaksiou;
        direction * dir;
        int speed;
    public:
        virtual vector<sensor_reading> extract_info();
        
};

class lidar_sensor : public sensors{
    private:
        vector<sensor_reading> lidar_readings;

    public:
        lidar_sensor(object *** xartis,position * posi,int tax,direction * dire);
        vector<sensor_reading> extract_info();
};

class radar_sensor : public sensors{
    private:
        vector<sensor_reading> radar_readings;
    public:
        radar_sensor(object *** map,position * posi,int tax,direction * dire);
        vector<sensor_reading> extract_info();

};

class camera_sensor : public sensors{
    private:
        vector<sensor_reading> camera_readings;
    public:
        camera_sensor(object *** xartis , position * posi , int tax,direction * dire);
        vector<sensor_reading> extract_info();
};


class self_driving_car; //forward declaration

class sensor_fusion_engine{
    private:
        lidar_sensor  * lidar;    
        radar_sensor * radar;
        camera_sensor * camera;

        vector<sensor_reading> fused_sensor_readings;
        vector<sensor_reading> lidar_readings;
        vector<sensor_reading> radar_readings;
        vector<sensor_reading> camera_readings;
    public:
        void extract_sensor_data();
        void fuse_sensor_data();
        int is_in(sensor_reading sr);
        sensor_fusion_engine(self_driving_car * amaksi);
        sensor_fusion_engine();
        ~sensor_fusion_engine();
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

        int get_x();
        
        int get_y();
        
        ~grid_world();

};



class self_driving_car : public object {
    private:
        lidar_sensor * lidar;
        radar_sensor * radar;
        camera_sensor * camera;
        sensor_fusion_engine fusing_engine;
        int speed;
        direction dir;
    public:
        self_driving_car(parameters p,grid_world * plegma);
        void accelerate();
        void decelerate();
        void forward();
        void turn();
        void extract_from_sensors();
        void print_direction();
        lidar_sensor * get_lidar_sensor_pointer();
        radar_sensor * get_radar_sensor_pointer();
        camera_sensor * get_camera_sensor_pointer();
        ~self_driving_car(); //TODO i allocated memory for the lidar and radar and cmaera sensor l,ao
};


class wall : public object {
    public:
        wall();
};

class moving_object:public object{ 
    protected:
        grid_world *plegma;
        int speed;
        direction dir;
    public:
        virtual void move();
        moving_object(grid_world* grid);
        int get_speed();
        direction get_dir();
        bool is_moving();
};

class static_object:public object{
    private:
    public:
        virtual bool is_moving();
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

class parked_car : public static_object{
    private:
        static int parked_car_count;
    public:
        parked_car(const parameters &p);
};

class trafic_light:public static_object{ //TODO den mou aresei auti i ilopoiisi
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