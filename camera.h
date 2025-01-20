#pragma once
#include "math/mat4.h"
#include "math/vector.h"
#include "euler.h"
#include "string.h"

float cameraScaler = 0.2f;
typedef struct Camera {
 Euler euler;
mat4f cameraMatrix;
mat4f cameraRotation;
mat4f finalCamera;
float cameraSpeed;
vector cameraPosition;
vector upVector;
vector rigth;
vector target;
vector forward;
float mouseX;
float mouseY;
float lastMouseX;
float lastMouseY;
vector upVectorRotaion;
vector forwardRotation;
vector rigthRotation;
} Camera;


void setCameraPosition(Camera* camera){
    camera->cameraMatrix[0][3] = -camera->cameraPosition.x;
    camera->cameraMatrix[1][3] = -camera->cameraPosition.y;
    camera->cameraMatrix[2][3] = -camera->cameraPosition.z;
}
void createCameraMatrix(Camera *camera){
    camera->target = (vector){0.f,0.f,-1.f};
   camera->upVector = (vector){0.f,1.f,0.f};
   camera->rigth = (vector){1.f,0.f,0.f};
   camera->forward =(vector){0.f};
camera->upVectorRotaion = (vector){0.f};
 camera->forwardRotation= (vector){0.f};
camera->rigthRotation = (vector){0.f};

   camera->cameraSpeed = 0.1f;
   camera->cameraPosition = (vector){0.f,0.f,0.f};
   camera->euler.p =0.f;
   camera->euler.y =0.f;
   camera->euler.r =0.f;
  camera->mouseX = 0.f ;
 camera->mouseY =0.f;
 camera->lastMouseX =0.f;
 camera->lastMouseY =0.f;
    mat4fFromVectors(&camera->cameraMatrix,camera->upVector,camera->rigth,camera->target,(vector){0.f,0.f,0.f});
    setForwards(camera->target,&camera->cameraMatrix);
    setUp(camera->upVector,&camera->cameraMatrix);
    setRight(camera->rigth,&camera->cameraMatrix);
    setCameraPosition(camera);
    camera->cameraMatrix[3][3] =1.f; 
    mat4fFromVectors(&camera->cameraRotation,camera->upVector,camera->rigth,camera->target,(vector){0.f,0.f,0.f});

    mat4fFromVectors(&camera->finalCamera,camera->upVector,camera->rigth,camera->target,(vector){0.f,0.f,0.f});
}


void cameraTransform(Camera* camera){
    
    vector N = camera->forwardRotation;
    normalize(N);
    vector U = camera->upVectorRotaion;
    normalize(U);
    U = cross(U,N);
    vector V = cross(N,U);


    camera->cameraRotation[0][0] = U.x;   camera->cameraRotation[0][1] = U.y;   camera->cameraRotation[0][2] = U.z;   camera->cameraRotation[0][3] = 0.0f;
    camera->cameraRotation[1][0] = V.x;   camera->cameraRotation[1][1] = V.y;   camera->cameraRotation[1][2] = V.z;   camera->cameraRotation[1][3] = 0.0f;
    camera->cameraRotation[2][0] = N.x;   camera->cameraRotation[2][1] = N.y;   camera->cameraRotation[2][2] = N.z;   camera->cameraRotation[2][3] = 0.0f;
    camera->cameraRotation[3][0] = 0.0f;  camera->cameraRotation[3][1] = 0.0f;  camera->cameraRotation[3][2] = 0.0f;  camera->cameraRotation[3][3] = 1.0f;

}

void buildViewMatrix(Camera* camera){
   mat4f temp = {0};
   temp[0][0]=camera->rigth.x;     temp[0][1]=camera->upVector.x;    temp[0][2]=-camera->forward.x; 
   temp[1][0]=camera->rigth.y;     temp[1][1]=camera->upVector.y;    temp[1][2]=-camera->forward.y;
   temp[2][0]=camera->rigth.z;     temp[2][1]=camera->upVector.z;    temp[2][2]=-camera->forward.z;
   temp[3][0] = 0;  
   temp[3][1] = 0;
   temp[3][2] = 0;
   temp[3][3] = 1;
  memcpy(camera->cameraRotation,&temp,sizeof(temp));
}


void moveCamera(Camera *camera){
    setForwards(camera->target,&camera->cameraMatrix);
    setUp(camera->upVector,&camera->cameraMatrix);
    setRight(camera->rigth,&camera->cameraMatrix);
    // memset(camera->cameraMatrix,0,sizeof(camera->cameraMatrix));
    // camera->cameraMatrix[0][0] = 1.f;
    // camera->cameraMatrix[1][1] = 1.f;
    // camera->cameraMatrix[2][2] = 1.f;
     camera->cameraMatrix[3][3] =1.f; 
    setCameraPosition(camera);
  multiplyMat4f2(camera->finalCamera,camera->cameraRotation,camera->cameraMatrix);
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


void calculateRotationMatrix(float pitch, float yaw, float roll, mat4f rotationMatrix) {
    float cp = cosf(pitch), sp = sinf(pitch);
    float cy = cosf(yaw), sy = sinf(yaw);
    float cr = cosf(roll), sr = sinf(roll);

    // Combine yaw, pitch, roll into rotation matrix
    rotationMatrix[0][0] = cy * cr;
    rotationMatrix[0][1] = sr * sp - sy * cp * cr;
    rotationMatrix[0][2] = sy * sp + sy * cp * sr;
    rotationMatrix[0][3] = 0.0f;

    rotationMatrix[1][0] = sy * cr;
    rotationMatrix[1][1] = -sy * sp * sr + cp * sr;
    rotationMatrix[1][2] = -sy * cp * cr + sp * sr;
    rotationMatrix[1][3] = 0.0f;

    rotationMatrix[2][0] = -sp;
    rotationMatrix[2][1] = cp * sr;
    rotationMatrix[2][2] = cp * cr;
    rotationMatrix[2][3] = 0.0f;

    rotationMatrix[3][0] = 0.0f;
    rotationMatrix[3][1] = 0.0f;
    rotationMatrix[3][2] = 0.0f;
    rotationMatrix[3][3] = 1.0f;
}


