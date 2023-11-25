#include "worm.h"

union BodyUserData {
    Worm* worm;
    // Otros tipos de datos que puedas necesitar.
};

Worm::Worm(b2World& world, int hitPoints, int direction, float x_pos, float y_pos, uint32_t id_) : 
            coleccionArmas(new ColeccionArmas(world)),armaActual(nullptr), moving(false) ,facingDirection(direction), airborne(false), hitPoints(hitPoints), initialHeight(0.0f),
            finalHeight(0.0f), jumpSteps(0), id(id_), status(WormStates::IDLE), angulo_disparo(0.0f), apuntando(false)
{
    b2BodyDef gusanoDef;
    gusanoDef.type = b2_dynamicBody;
    // printf("La posicion en el constructo es %f  %f\n",x_pos,y_pos);
    gusanoDef.position.Set(x_pos, y_pos);

    BodyUserData userData;
    userData.worm = this;
    gusanoDef.userData.pointer = reinterpret_cast<uintptr_t>(userData.worm);

    b2Body *gusano = world.CreateBody(&gusanoDef);
    this->body = gusano;
    

    b2PolygonShape gusanoBox;
    gusanoBox.SetAsBox(BOX_WIDTH, BOX_HEIGHT);

    b2FixtureDef fixtureGusano;
    fixtureGusano.shape = &gusanoBox;
    fixtureGusano.density = WORM_DENSITY;
    fixtureGusano.friction = WORM_FRICTION;
    fixtureGusano.filter.categoryBits = CollisionCategories::WORM_COLL;
    fixtureGusano.filter.maskBits = (CollisionCategories::BOUNDARY_COLL | CollisionCategories::PROJECTILE_COLL);
    fixtureGusano.filter.maskBits &= ~CollisionCategories::WORM_COLL;
              
    this->body->SetFixedRotation(true); // Evita que rote

    this->body->CreateFixture(&fixtureGusano);
    // printf("luego de crearle las fixtures la posicion del gusano es %f   %f\n", body->GetPosition().x, body->GetPosition().y);
}

bodyType Worm::identificar() {
    return bodyType::WORM;
}

void Worm::StartMovement(int dir) {
    if (this->isAirborne()) return;
    facingDirection = dir;
    moving = true;
}

void Worm::Move() {
    b2Vec2 velocity = body->GetLinearVelocity();
    float desiredVel = 0;
    switch(facingDirection) {
        case RIGHT:
            desiredVel = MOVING_SPEED;
            break;
        case LEFT:
            desiredVel = -1 * MOVING_SPEED;
            break;
    }
    float velChange = desiredVel - velocity.x;
    status = WormStates::WALK;
    float impulse = body->GetMass() * velChange;
    body->ApplyLinearImpulse( b2Vec2 (impulse, 0), body->GetWorldCenter(), true);
}

void Worm::Stop() {
    moving = false;
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;
    body->SetLinearVelocity(velocity);
    status = WormStates::IDLE;
}

void Worm::JumpForward() {
    if (this->isAirborne()) return;
    if (this->isMoving()) Stop();
    jumpSteps = FORWARD_JUMP_STEPS;
    float impulse = body->GetMass() * FORWARD_JUMP_IMPULSE_MULTIPLIER;
    body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);

    b2Vec2 velocity = body->GetLinearVelocity();
    switch(facingDirection) {
        case RIGHT:
            velocity.x = FORWARD_JUMP_X_VELOCITY;
            break;
        case LEFT:
            velocity.x = -1 * FORWARD_JUMP_X_VELOCITY;
            break;
    }
    body->SetLinearVelocity(velocity);
    //state = WormStates::JUMP;
}

void Worm::JumpBackward() {
    if (this->isAirborne()) return;
    if (this->isMoving()) Stop();
    jumpSteps = BACKWARD_JUMP_STEPS;
    float impulse = body->GetMass() * BACKWARD_JUMP_IMPULSE_MULTIPLIER;
    body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);

    b2Vec2 velocity = body->GetLinearVelocity();
    switch(facingDirection) {
        case RIGHT:
            velocity.x = -1 * BACKWARD_JUMP_X_VELOCITY;
            break;
        case LEFT:
            velocity.x = BACKWARD_JUMP_X_VELOCITY;
            break;
    }
    body->SetLinearVelocity(velocity);
    //state = WormStates::BACKFLIP;
}

void Worm::startGroundContact() {
    airborne = false;
    b2Vec2 position = body->GetPosition();
    finalHeight = position.y;
    float heightDiff = initialHeight - finalHeight;
    if (heightDiff < 2) return;
    if (2 < heightDiff && heightDiff < 25) {
        takeDamage((int)heightDiff);
    }
    else if (heightDiff >= 25){
        takeDamage(25);
    }
        
}

void Worm::endGroundContact() {
    airborne = true;
    b2Vec2 position = body->GetPosition();
    initialHeight = position.y;
}

bool Worm::isMoving() {
    return moving;
}

void Worm::startWaterContact() {
    this->hitPoints = 0;
}

bool Worm::isAirborne() {
    return airborne;
}

void Worm::takeDamage(int damage) {
    hitPoints -= damage;
}

std::vector<float> Worm::GetPosition() {
    b2Vec2 position = body->GetPosition();
    // printf("Al pedire la posicion se devuelve %f   %f\n",position.x,position.y);
    return std::vector<float> ({position.x, position.y});
}

float Worm::GetAngle() {
    return body->GetAngle();
}

Projectile* Worm::usar_arma() {
    b2Vec2 position = body->GetPosition();
    float angle;
    if(this->facingDirection == LEFT){
        angle = this->aiming_angle() + 1.57;
    }
    else{
        angle = this->aiming_angle();
    }
    printf("el angulo con el que se dispara es %f\n",angle);
    return armaActual->Shoot(position.x, position.y, angle);
}

int Worm::get_facing_direction(){
    return this->facingDirection;
}

uint32_t Worm::get_id(){
    return this->id;
}

float Worm::get_angulo(){
    return this->body->GetAngle();
}

uint8_t Worm::get_status(){
    return this->status;
}

void Worm::cambiar_arma(uint8_t id_arma){
    if (isAirborne()){
        return;
    }
    
    switch (id_arma)
    {
    case Armas::BAZOOKA:
        status = WormStates::BAZOOKA_AIMING;
        break;
    
    case Armas::MORTERO:
        status = WormStates::MORTAR_AIMING;
        break;
    
    case Armas::GRANADA:
        status = WormStates::GREEN_GRENADE_AIMING;
        break;
    
    case Armas::DINAMITA:
        status = WormStates::DINAMITA_AIMING;
        break;
    
    case Armas::BATE:
        status = WormStates::BATE_AIMING;
        break;
    
    case Armas::ATAQUE_AEREO:
        status = WormStates::AIR_ATTACK_AIMING;
        break;
    
    case Armas::GRANADA_SANTA:
        status = WormStates::HOLY_GRANADE_AIMING;
        break;
    
    case Armas::GRANADA_ROJA:
        status = WormStates::RED_GRENADE_AIMING;
        break;
    
    case Armas::BANANA:
        status = WormStates::BANANA_AIMING;
        break;
    
    case Armas::TELETRANSPORTACION:
        status = WormStates::TELEPORT_AIMING;
        break;
    
    default:
        break;
    }

    armaActual = coleccionArmas->SeleccionarArma(id_arma);
}

void Worm::iniciar_carga() {
    if(!this->armaActual){
        return;
    }
    this->armaActual->iniciarCarga();
}

void Worm::cargar_arma(){
    if(!this->armaActual){
        printf("no tiene un arma\n");
        return;
    }
    printf("tiene arma\n");
    this->armaActual->cargar();
}

bool Worm::esta_cargando_arma() {
    if(!this->armaActual){
        return false;
    }
    return this->armaActual->estaCargando();
}

void Worm::esta_apuntando_para(bool id){
    apuntando = true;
    this->esta_apuntando_para_arriba= id;
}

bool Worm::esta_apuntando(){
    return apuntando;
}

void Worm::incrementar_angulo_en(float inc){
    if(!esta_apuntando_para_arriba){
        inc = -inc;
    }
    if(angulo_disparo + inc < -1.57 || angulo_disparo + inc > 1.57){
        return;
    }
    angulo_disparo +=inc;
}

void Worm::detener_acciones(){
    if(!airborne){
        angulo_disparo = 0;
        apuntando = false;
        status = WormStates::IDLE;
        this->Stop();
    }
}

float Worm::aiming_angle(){
    return angulo_disparo;
}

void Worm::parar_angulo(){
    apuntando = false;
}

uint8_t Worm::get_vida() {
    return hitPoints;
}

void Worm::cambiar_direccion(uint8_t dir){
    switch (dir)
    {
    case (RIGHT):
        {
            // printf("Se recibe comando cambiar_direccion a derecha\n");
            this->facingDirection = RIGHT;
            break;
        }
    case (LEFT):{
        // printf("Se recibe comando cambiar direccino a izquerda\n");
        this->facingDirection = LEFT;
        break;
    }
    }
}

bool Worm::isDead() {
    return (this->hitPoints <= 0) ? true : false;
}

void Worm::kill() {
    this->hitPoints = 0;
    //delete this->coleccionArmas;
}

