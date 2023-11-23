#ifndef PROJECTILE_GENERATOR_H
#define PROJECTILE_GENERATOR_H

#include "../comunicacion/projectile.h"
#include "missile.h"

#define PROYECTILE_MISSILE 1


class ProjectileGenerator {
    public:
/*
 * Devuelve el proyectil con el codigo pasado por parametro
 * Descripcion de parametros:
 * `proy_code`: Codigo de proyectil recibido por server.
 * `pos_x`: Posicion en x
 * `pos_y`: Posicion en y
 * `angle`: Angulo (angulo=0 => mira a derecha)
 */
    static std::unique_ptr<Projectile> get_proyectile_with_code(int proy_code,
                                                            float& pos_x,
                                                            float& pos_y,
                                                            float& angle);
};

#endif