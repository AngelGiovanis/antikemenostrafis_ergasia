#include <stdio.h>
#include  "../include/types.h"


int main(int argc, char * argv ){
    if (argc < 3){
        cout<<"program should be called as ./program name target_x target_y"<<endl;
        return 1;
    }
    return 0;
}