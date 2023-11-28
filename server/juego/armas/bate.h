#ifndef BATE_H
#define BATE_H

#include "arma.h"
#include "../worm.h"
#include "../worm_query.h"

#define HITBOX_OFFSET 1.5f
#define HITBOX_HALF_SIDE 0.75f

#define IMPULSE_X 3.0f
#define IMPULSE_Y 4.0f

class Bate : public Arma {
private:
    b2World& world;
    const int dmg;
public:
    Bate(b2World& world, int dmg);
    virtual bool isGrenade() override;
    virtual bool isRocket() override;
    virtual void iniciarCarga() override;
    virtual void cargar() override;
    virtual Projectile* Shoot(float x_pos, float y_pos, float angle) override;
};

#endif
