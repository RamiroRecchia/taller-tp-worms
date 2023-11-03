#ifndef WORM_WRAPPER_H
#define WORM_WRAPPER_H

#include <vector>

//Direcciones (despues quizas cambie a un angulo)
#define DIR_RIGHT 1
#define DIR_LEFT 0

//Estados (Despues va a haber mas)
#define STATUS_IDLE 0
#define STATUS_MOVING 1

class WormWrapper {
    private:
    std::vector<float> position;  // (x,y)
    int dir;                    // Despues quizas cambie a un angulo
    int status;                 
    
    public:
    //Constructor
    WormWrapper(std::vector<float> position, int dir, int status);

    std::vector<float> get_position();
};

#endif