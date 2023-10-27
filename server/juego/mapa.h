#ifndef MAPA_H
#define MAPA_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include <vector>

// Copyright (c) 2019 Erin Catto

#define MOVE_RIGHT 0
#define MOVE_LEFT 1

class Mapa {
private:
  b2World world;
  std::vector<b2Body *> gusanos;
  const float timeStep = 1.0f / 60.0f;
  const int32 velocityIterations = 6;
  const int32 positionIterations = 2;

  int32 steps = 0; // para debuggear.

public:
  Mapa();
  void Step();
  /*
   * Setea la velocidad del gusano dado por idx, que es el
   * indice en el vector gusanos del gusano a mover.
   * Si dir es 0, se mueve a la derecha. Si es 1, a la izquierda.
   * */
  void MoveWorm(int idx, int dir);
  /*
   * Setea la velocidad del gusano cuyo indice es idx a 0.
   * */
  void StopWorm(int idx);
};

#endif
