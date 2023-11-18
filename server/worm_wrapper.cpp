#include "worm_wrapper.h"

WormWrapper::WormWrapper(std::vector<float> position, uint8_t dir, uint8_t status, uint32_t id_, float angulo_, float angulo_disparo_): 
            position(position), dir(dir), status(status), id(id_), angulo(angulo_),angulo_disparo(angulo_disparo_) {}

std::vector<float> WormWrapper::get_position(){
    return position;
}
uint8_t WormWrapper::get_direccion(){
    return this->dir;
}

uint8_t WormWrapper::get_estado(){
    return this->status;
}

float WormWrapper::get_angulo(){
    return this->angulo;
}

uint32_t WormWrapper::get_id(){
    return this->id;
}

float WormWrapper::get_angulo_disparo(){
    return this->angulo_disparo;
}