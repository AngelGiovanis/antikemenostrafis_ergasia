#include "types.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

class gene{
    private:
        string alilouxia;
    public:
        gene(string &al)
            :alilouxia(al){}
        
        void get_alilouxia(string &al) const{
            al = alilouxia;
        }
};


class nucleus{
    private:
        vector<gene*> alilouxies_dna;
    public:
        int is_valid(string &alilouxia){
            for(int i = 0; i < alilouxia.size(); i++){
                if(alilouxia[i] != 'A' || alilouxia[i] != 'T' || alilouxia[i] != 'C' || alilouxia[i] != 'G'){
                    return 0;
                }
            }
            return 1;
        }

        void set_alilouxia(string &alilouxia){
            alilouxies_dna.push_back(new gene(alilouxia));
        }
};

class Cell{
    private:
        nucleus pirinas;
    public:
        ~Cell();
        Cell();
        

};

int main(int argc,char *argv[]){

    int valid_alilouxies = 0;

    int alilouxies_count = atoi(argv[1]);
    int rivosomata_count= atoi(argv[2]);
    int epanalipseis_count = atoi(argv[3]);

    string current_alilouxia;

    Cell kittaro;

    while(valid_alilouxies < alilouxies_count){
        cout<<"give us a alilouxia dna: ";
        cin>>current_alilouxia;
        cout<<endl;


        valid_alilouxies++;

    }
    
    return 0;
}