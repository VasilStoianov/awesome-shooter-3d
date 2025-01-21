#pragma once
#include "vector.h"

typedef struct Euler{
  float p;
  float y;
  float r;
} Euler;


vector eulerToVector(Euler euler){
   vector res = {0};
   res.x = cosf(euler.y) * cosf(euler.p);
   res.y = sinf(euler.p);
   res.z = sinf(euler.y) * cosf(euler.p);
  return res;
}