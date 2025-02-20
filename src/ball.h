#ifndef BALL_H_
#define BALL_H_

#include "./physics.h"
#include "./screen.h"

typedef struct {
  physics_body body;
  float radius;
  float bounce;
} ball;

ball create_ball(physics_body body, float radius, float bounce) {
  return (ball){.body = body, .radius = radius, .bounce = bounce};
}

void update_ball(ball *b, int w, int h, float dt, bool *buffer) {
  physics_simulate(&b->body, dt);
  vf c = b->body.pos;
  float r = b->radius;

  // bounce
  if (c.x + r > w) {
    b->body.pos.x = w - r;
    b->body.vel = vf_mul(b->body.vel, vf_makeff(-b->bounce, 1.0f));
  }
  if (c.x - r < 0) {
    b->body.pos.x = r;
    b->body.vel = vf_mul(b->body.vel, vf_makeff(-b->bounce, 1.0f));
  }
  if (c.y + r > h) {
    b->body.pos.y = h - r;
    b->body.vel = vf_mul(b->body.vel, vf_makeff(1.0f, -b->bounce));
  }
  if (c.y - r < 0) {
    b->body.pos.y = r;
    b->body.vel = vf_mul(b->body.vel, vf_makeff(1.0f, -b->bounce));
  }

  draw_circle(c, r, buffer, w, h);
}

#endif // BALL_H_
