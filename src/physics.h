#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "./vec.h"

typedef struct {
  vf pos;
  vf vel;
  vf acc;
} physics_body;

physics_body create_body(vf pos, vf vel, vf acc) {
  return (physics_body){.pos = pos, .vel = vel, .acc = acc};
}

void physics_simulate(physics_body *body, float dt) {
  vf dtv = vf_makef(dt);
  body->pos = vf_add(body->pos, vf_mul(body->vel, dtv));
  body->vel = vf_add(body->vel, vf_mul(body->acc, dtv));
}

#endif // PHYSICS_H_
