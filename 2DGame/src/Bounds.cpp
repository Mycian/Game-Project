#include "Bounds.h"


Bounds::Bounds()
{
    //ctor
}

Bounds::~Bounds()
{
    //dtor
}

bool Bounds::checkCollision(int checkX, int checkY){
    if(checkX > 310 || checkX < -225 || checkY > 150 || checkY < -110)
        return 0;


//    for (int i = 0; i < points-1; i++ ){
//        if(((checkX - x[i])*(y[i+1] - y[i]) - (checkY - y[i])*(x[i+1] - x[i])) < 0){
//            std::cout << "outside bounds" << std::endl;
//            return 0;
//        }
//    }
    return 1;
}
