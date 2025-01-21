#pragma once
#include "GLFW/glfw3.h"
#include "euler.h"
#include "math/mat4.h"
#include "math/vector.h"
#include "string.h"

float cameraScaler = 3.f;
float dt = 0.016666667;
typedef struct Camera {
  Euler euler;
  mat4f cameraMatrix;
  mat4f cameraRotation;
  mat4f finalCamera;
  float cameraSpeed;
  vector cameraPosition;
  vector upVector;
  float mouseX;
  float mouseY;
  float lastMouseX;
  float lastMouseY;
  vector upVectorRotaion;
  vector forwardRotation;
  vector rigthRotation;
} Camera;

void setCameraPosition(Camera *camera) {
  camera->cameraMatrix[0][3] = -camera->cameraPosition.x;
  camera->cameraMatrix[1][3] = -camera->cameraPosition.y;
  camera->cameraMatrix[2][3] = -camera->cameraPosition.z;
}
void createCameraMatrix(Camera *camera) {
  camera->upVector = (vector){0.f, 1.f, 0.f};
  camera->upVectorRotaion = (vector){0.f,1.f,.0f};
  camera->forwardRotation = (vector){0.f,0.f,1.f};
  camera->rigthRotation = (vector){1.f,0.f,0.f};
  camera->cameraSpeed = 0.1f;
  camera->cameraPosition = (vector){0.f, 0.f, 0.f};
  camera->euler.p = 0.f;
  camera->euler.y = 0.f;
  camera->euler.r = 0.f;
  camera->mouseX = 0.f;
  camera->mouseY = 0.f;
  camera->lastMouseX = 0.f;
  camera->lastMouseY = 0.f;
  mat4fFromVectors(&camera->cameraMatrix, camera->upVector, camera->rigthRotation,
                   camera->forwardRotation, (vector){0.f, 0.f, 0.f});
  setForwards(camera->forwardRotation, &camera->cameraMatrix);
  setUp(camera->upVector, &camera->cameraMatrix);
  setRight(camera->rigthRotation, &camera->cameraMatrix);
  setCameraPosition(camera);
  camera->cameraMatrix[3][3] = 1.f;
  mat4fFromVectors(&camera->cameraRotation, camera->upVector, camera->rigthRotation,
                   camera->forwardRotation, (vector){0.f, 0.f, 0.f});
  mat4fFromVectors(&camera->finalCamera, camera->upVector, camera->rigthRotation,
                   camera->forwardRotation, (vector){0.f, 0.f, 0.f});
}

void cameraTransform(Camera *camera) {

  vector eul = eulerToVector(camera->euler);
  memcpy(&camera->forwardRotation, &eul, sizeof(eul));
  normalize(camera->forwardRotation);
  camera->rigthRotation =
      cross(camera->forwardRotation, (vector){0.f, 1.0f, 0.f});
  normalize(camera->rigthRotation);

  camera->upVectorRotaion =
      cross(camera->rigthRotation, camera->forwardRotation);
  
      // cross(camera->forwardRotation,camera->rigthRotation );
  normalize(camera->upVectorRotaion);

  vector N = camera->forwardRotation;
  normalize(N);
  vector U = camera->upVectorRotaion;
  normalize(U);
  U = cross(U, N);
  vector V = cross(N, U);

  camera->cameraRotation[0][0] = U.x;
  camera->cameraRotation[0][1] = U.y;
  camera->cameraRotation[0][2] = U.z;
  camera->cameraRotation[0][3] = 0.0f;
  camera->cameraRotation[1][0] = -V.x;
  camera->cameraRotation[1][1] = -V.y;
  camera->cameraRotation[1][2] = -V.z;
  camera->cameraRotation[1][3] = 0.0f;
  camera->cameraRotation[2][0] = N.x;
  camera->cameraRotation[2][1] = N.y;
  camera->cameraRotation[2][2] = N.z;
  camera->cameraRotation[2][3] = 0.0f;
  camera->cameraRotation[3][0] = 0.0f;
  camera->cameraRotation[3][1] = 0.0f;
  camera->cameraRotation[3][2] = 0.0f;
  camera->cameraRotation[3][3] = 1.0f;
}

void moveCamera(Camera *camera) {
  // setForwards(camera->forwardRotation, &camera->cameraMatrix);
  // setUp(camera->upVector, &camera->cameraMatrix);
  // setRight(camera->forwardRotation, &camera->cameraMatrix);
  identity(&camera->cameraMatrix);
  camera->cameraMatrix[3][3] = 1.f;
  setCameraPosition(camera);
  multiplyMat4f2(camera->finalCamera, camera->cameraRotation,
                 camera->cameraMatrix);
}
void handleCameraMovement(GLFWwindow *window, int key, Camera *camera) {

  switch (key) {
  case GLFW_KEY_UP: {

    subtractVector(&camera->cameraPosition,
                   scaleAndReturn(&camera->upVector, cameraScaler * dt));

    break;
  }
  case GLFW_KEY_DOWN: {

    addToVector(&camera->cameraPosition,
                scaleAndReturn(&camera->upVector, cameraScaler * dt));

    break;
  }
  case GLFW_KEY_D: {
    vector left = cross(camera->upVector, camera->forwardRotation);
    normalize(left);
    addToVector(&camera->cameraPosition,
                scaleAndReturn(&left, cameraScaler * dt));
    break;
  }

  case GLFW_KEY_A: {
    vector left = cross(camera->forwardRotation, camera->upVector);
    normalize(left);
    addToVector(&camera->cameraPosition,
                scaleAndReturn(&left, cameraScaler * dt));
    break;
  }

  case GLFW_KEY_S: {
    vector forward = cross(camera->upVectorRotaion, camera->rigthRotation);
    normalize(forward);

    addToVector(&camera->cameraPosition,
                scaleAndReturn(&forward, cameraScaler * dt));
    break;
  }

  case GLFW_KEY_W: {
    vector backwards = cross(camera->rigthRotation, camera->upVector);
    normalize(backwards);

    addToVector(&camera->cameraPosition,
                scaleAndReturn(&backwards, cameraScaler * dt));
    break;
  }

  default:
    break;
  }
  moveCamera(camera);
}