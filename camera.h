#include "math/mat4.h"
#include "math/vector.h"


float cameraScaler = 0.2f;
typedef struct Camera {

mat4f cameraMatrix;
mat4f cameraRotation;
mat4f finalCamera;
float cameraSpeed;
vector cameraPosition;
vector upVector;
vector rigth;
vector target;

} Camera;


void setCameraPosition(Camera* camera){
    camera->cameraMatrix[0][3] = -camera->cameraPosition.x;
    camera->cameraMatrix[1][3] = -camera->cameraPosition.y;
    camera->cameraMatrix[2][3] = -camera->cameraPosition.z;
}
void createCameraMatrix(Camera *camera){
    camera->target = (vector){0.f,0.f,1.f};
   camera->upVector = (vector){0.f,1.f,0.f};
   camera->rigth = (vector){1.f,0.f,0.f};
   camera->cameraSpeed = 0.1f;
   camera->cameraPosition = (vector){0.f,0.f,0.f};
   
    mat4fFromVectors(&camera->cameraMatrix,camera->upVector,camera->rigth,camera->target,(vector){0.f,0.f,0.f});
    setForwards(camera->target,&camera->cameraMatrix);
    setUp(camera->upVector,&camera->cameraMatrix);
    setRight(camera->rigth,&camera->cameraMatrix);
    setCameraPosition(camera);
    camera->cameraMatrix[3][3] =1.f; 
    mat4fFromVectors(&camera->cameraRotation,camera->upVector,camera->rigth,camera->target,(vector){0.f,0.f,0.f});

    mat4fFromVectors(&camera->finalCamera,camera->upVector,camera->rigth,camera->target,(vector){0.f,0.f,0.f});
}



void moveCamera(Camera *camera){
    setForwards(camera->target,&camera->cameraMatrix);
    setUp(camera->upVector,&camera->cameraMatrix);
    setRight(camera->rigth,&camera->cameraMatrix);
    setCameraPosition(camera);
    camera->cameraMatrix[3][3] =1.f; 
  multiplyMat4f2(camera->finalCamera,camera->cameraRotation,camera->cameraMatrix);
}



void cameraTransform(Camera* camera){
    
    vector N = camera->target;
    normalize(N);
    vector U = camera->upVector;
    normalize(U);
    U = cross(U,N);
    vector V = cross(N,U);


    camera->cameraRotation[0][0] = U.x;   camera->cameraRotation[0][1] = U.y;   camera->cameraRotation[0][2] = U.z;   camera->cameraRotation[0][3] = 0.0f;
    camera->cameraRotation[0][0] = V.x;   camera->cameraRotation[1][1] = V.y;   camera->cameraRotation[1][2] = V.z;   camera->cameraRotation[1][3] = 0.0f;
    camera->cameraRotation[2][0] = N.x;   camera->cameraRotation[2][1] = N.y;   camera->cameraRotation[2][2] = N.z;   camera->cameraRotation[2][3] = 0.0f;
    camera->cameraRotation[3][0] = 0.0f;  camera->cameraRotation[3][1] = 0.0f;  camera->cameraRotation[3][2] = 0.0f;  camera->cameraRotation[3][3] = 1.0f;

  
}

void handleCameraMovement(GLFWwindow *window, int key, Camera *camera){
  
  switch (key)
  {
  case GLFW_KEY_UP:{
    
     subtractVector(&camera->cameraPosition, scaleAndReturn(&camera->upVector,cameraScaler));
  
    break;
  }
case GLFW_KEY_DOWN:{
    
      addToVector(&camera->cameraPosition, scaleAndReturn(&camera->upVector,cameraScaler));
  
    break;
  }
  case GLFW_KEY_LEFT:
  {
    vector left = cross(camera->upVector,camera->target);
    normalize(left);
    addToVector(&camera->cameraPosition,scaleAndReturn(&left,cameraScaler));
    break;
  }

case GLFW_KEY_RIGHT:
  {
    vector left = cross(camera->target,camera->upVector);
    normalize(left);
    addToVector(&camera->cameraPosition,scaleAndReturn(&left,cameraScaler));
    break;
  }

  case GLFW_KEY_KP_ADD:{
     vector forward = cross(camera->upVector,camera->rigth);
     normalize(forward);

    addToVector(&camera->cameraPosition,scaleAndReturn(&forward,cameraScaler));
    break;
  }

case GLFW_KEY_KP_SUBTRACT:{
     vector backwards = cross(camera->rigth,camera->upVector);
     normalize(backwards);

    addToVector(&camera->cameraPosition,scaleAndReturn(&backwards,cameraScaler));
    break;
  }
  
  default:
    break;
  
  }
  moveCamera(camera);
}


