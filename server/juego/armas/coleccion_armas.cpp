#include "./coleccion_armas.h"

ColeccionArmas::ColeccionArmas(b2World& world) : world(world)
{
    GameConfig& config = GameConfig::getInstance();
    armas[Armas::BAZOOKA] = new Bazooka(world, config.bazooka_dmg, config.bazooka_radius);
}

Arma* ColeccionArmas::SeleccionarArma(Armas arma)
{
    return armas[arma];
}

ColeccionArmas::~ColeccionArmas()
{
    for (auto arma : armas) {
        delete arma.second;
    }
}
