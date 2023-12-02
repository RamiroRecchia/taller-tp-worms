#include "beam.h"

BeamServer::BeamServer(b2World& world, int type, float x_pos, float y_pos, float angle):Colisionable(bodyType::BEAM) {
    float transforamtion = angle/180;
    b2BodyDef vigaDef;
    vigaDef.position.Set(x_pos, y_pos);
    vigaDef.angle = transforamtion;
    vigaDef.userData.pointer = reinterpret_cast<uintptr_t> (this);
    b2Body *viga = world.CreateBody(&vigaDef);
    this->body = viga;
    // printf("El angulo con el que se crea es %f\n",viga->GetAngle());
    b2PolygonShape vigaBox;
    float length = (type == SMALL) ? SMALL_LENGTH : LARGE_LENGTH;
    this->len = length;
    vigaBox.SetAsBox(length, HEIGHT);
    

    b2FixtureDef fixtureViga;
    fixtureViga.shape = &vigaBox;
    fixtureViga.density = BEAM_DENSITY;
    fixtureViga.friction = BEAM_FRICTION;
    fixtureViga.restitutionThreshold = BEAM_RESTITUTION_THRESHOLD;
    fixtureViga.filter.categoryBits = CollisionCategories::BOUNDARY_COLL;
    fixtureViga.filter.maskBits = (CollisionCategories::WORM_COLL | CollisionCategories::PROJECTILE_COLL);

    this->body->CreateFixture(&fixtureViga);
}

// bodyType BeamServer::identificar() {
//     return bodyType::BEAM;
// }

std::vector<float> BeamServer::get_pos(){
    // printf("el angulo que se devuelve es %f\n",body->GetAngle());
     std::vector<float> viga({body->GetPosition().x,body->GetPosition().y,body->GetAngle(),2 * this->len});
     return viga;
}
