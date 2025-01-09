#include "math/mat4.h"
#include "math/vector.h"


typedef struct Camera {

mat4f cameraMatrix;
vector cameraPosition;


} Camera;

void createCameraMatrix(Camera *camera){
    setForwards((vector){1.f,0.f,0.f},&camera->cameraMatrix);
    setUp((vector){0.f,1.f,0.f},&camera->cameraMatrix);
    setRight((vector){0.f,0.f,1.f},&camera->cameraMatrix);
    camera->cameraMatrix[3][3] =1.f; 
}

void setCameraPosition(Camera* camera,vector cameraPos){
    camera->cameraMatrix[0][3] = -cameraPos.x;
    camera->cameraMatrix[1][3] = -cameraPos.y;
    camera->cameraMatrix[2][3] = -cameraPos.z;
}
