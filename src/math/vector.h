#pragma once
#include "math.h"

typedef struct vector
{
   float x;
   float y;
   float z;
} vector;

void scale(vector *vec, float scalar){
   vec->x *= scalar;
   vec->y *= scalar;  
   vec->z *= scalar;
}

vector vectorAddition(vector a, vector b){
     vector res = {0};
      res.x = a.x + b.x;
      res.y = a.y + b.y;
      res.z = a.z + b.z;
    return res;
}

void addToVector(vector *toAdd, vector forAdd){
      toAdd->x += forAdd.x;
      toAdd->y += forAdd.y;
      toAdd->z += forAdd.z;
}

vector subtract(vector a, vector b){
    vector res = {0};
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
   return res;

}

float vectorLength(vector a){
    return sqrtf((a.x *a.x) + (a.y * a.y) + (a.z * a.z));
}


float dot(vector a, vector b){
   return a.x * b.x + a.y + b.y + a.z * b.z;    
}

vector normalize(vector a){
    vector res = {0};
    float length = vectorLength(a);
    res.x = a.x/length;
    res.y = a.y/length;
    res.z = a.z/length;
    return res;
}


vector cross(vector a, vector b){
   vector res  = {0};
   res.x = a.y * b.z -a.z * b.y;
   res.y = a.z*b.x - a.x*b.z;
   res.z = a.x*b.y - a.y*b.x;
   return res;
}

