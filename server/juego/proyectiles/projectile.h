#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../../../box2d/include/box2d/box2d.h"
#include "../colisionable.h"

class Projectile : public Colisionable 
{
protected:
    b2Body* body;
    bool exploded = false;
    void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower)
    {
        b2Vec2 blastDir = applyPoint - blastCenter;
        float distance = blastDir.Normalize();
        if (distance == 0)
            return;

        float inverseDistance = 1 / distance;
        float impulseMagnitude = blastPower * inverseDistance * inverseDistance;
        body->ApplyLinearImpulse(impulseMagnitude * blastDir, applyPoint, true);
    }

public:
    Projectile() {};
    virtual bodyType identificar() override {
        return bodyType::PROJECTILE;
    }
    virtual bool hasExploded() {
        return exploded;
    }
    virtual b2Vec2 getPosition() {
        return body->GetPosition();
    }
    virtual float getAngle() {
        return body->GetAngle();
    }
    virtual void updateAngle() {
        b2Vec2 velocity = body->GetLinearVelocity();
        float newAngle = atan2(velocity.x, velocity.y);
        body->SetTransform(body->GetPosition(), newAngle);
    }
    virtual void explotar() = 0;
    virtual ~Projectile() {}
};

#endif
