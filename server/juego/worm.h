#ifndef WORM_H
#define WORM_H

#include "../../libs/box2d/include/box2d/box2d.h"

enum directions {
    RIGHT = 0,
    LEFT = 1,
};

#define BOX_WIDTH 0.15f
#define BOX_HEIGHT 0.4f

#define WORM_DENSITY 1.0f
#define WORM_FRICTION 0.0f

#define MOVING_SPEED 0.2

#define FORWARD_JUMP_STEPS 38
#define BACKWARD_JUMP_STEPS 58

#define FORWARD_JUMP_IMPULSE_MULTIPLIER 3.25
#define BACKWARD_JUMP_IMPULSE_MULTIPLIER 5

#define FORWARD_JUMP_X_VELOCITY 1.62
#define BACKWARD_JUMP_X_VELOCITY 0.2

class Worm {
private:
    b2Body* body;
    int facingDirection;
    bool airborne;
    int hitPoints;
    float initialHeight;
    float finalHeight;

public:
    int jumpSteps;
    uint32_t id;
    uint8_t status;
    float angulo;
    float angulo_disparo;
    bool esta_apuntando_para_arriba;
    bool apuntando;

    Worm(b2World& world, int hitPoints, int direction, float x_pos, float y_pos, uint16 collisionCategory, uint16 collisionMask,uint32_t id);
    void Move(int dir);
    void Stop();
    void JumpForward();
    void JumpBackward();
    void startGroundContact();
    void endGroundContact();
    bool isAirborne();
    void takeDamage(int damage);

    b2Vec2 GetPosition();

    int get_facing_direction();

    uint32_t get_id();

    uint8_t get_status();

    float get_angulo();

    void cambiar_arma(uint8_t tipo_arma);

    void esta_apuntando_para(bool dir);

    bool apuntando_para_arriba(bool dir);

    void incrementar_angulo_en(float inc);

    bool esta_apuntando();

    void cambiar_angulo();

    void detener_acciones();

    float aiming_angle();

    void parar_angulo();
};

#endif
