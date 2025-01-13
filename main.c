
#include "glad.h"

#include "GLFW/glfw3.h"
#include "camera.h"
#include "cube.h"
#include "image.h"
#include "math.h"
#include "math/mat4.h"
#include "math/vector.h"
#include "stdio.h"
#include "vertex.h"

int key_pressed[GLFW_KEY_LAST] = {0};
float zMove = 0.0;
float zMinus = 0.0;
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, int key, int scancode, int action,
                  int mods);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return -1;
  }

  // build and compile our shader zprogram
  // ------------------------------------

  char filepath[10] = "";
  Vertex vertex = createVertex(filepath);
  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // load and create a texture
  // -------------------------
  Image image;
  loadImage("resources/container.jpg", &image);

  Cube *cube = malloc(sizeof(Cube));
  Camera *camera = malloc(sizeof(Camera));
  glfwSetWindowUserPointer(window, camera);

  identityCubeMatrices(cube);

  float angle = 45.f;
  float angleMult = 1;

  setRotationY(angle, cube->rotate);
  setRotationX(angle, cube->rotate);
  setTranslation((vector){0.f, 0.f, 1.f}, cube->translate);
  // setScale((vector){0.5f,0.5f,0.5f},&cube->scale);

  mat4f projection = {0};
  createProjection(90.f, &projection, SCR_HEIGHT, SCR_WIDTH, 0.1f, 100.f);

  createCameraMatrix(camera);
  camera->cameraPosition = (vector){0.f, 0.f, 0.f};
  setCameraPosition(camera);

  glEnable(GL_DEPTH_TEST);
  // glCullFace(GL_BACK);
  glfwSetKeyCallback(window, processInput);

  float camX = .01f;
  while (!glfwWindowShouldClose(window)) {

    float dt = 1.0 / 60.f;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float scaleSpeed = 0.5f; // Adjust speed of scaling
    angle += angleMult;
    if (angle > 90 || angle < -90) {
      angleMult *= -1;
    }

    setRotationX(toRad(angle), cube->rotateX);

    setTranslation((vector){0.f, 0.f, -1.5f}, cube->translate);
    multiplyMat4f2(cube->rotate, cube->rotateY, cube->rotateX);
    transform(cube->transform, cube->translate, cube->rotate, cube->scale);

    setUniformMatrix4f("transform", vertex.id, cube->transform);
    setUniformMatrix4f("projection", vertex.id, projection);
    setUniformMatrix4f("camera", vertex.id, camera->finalCamera);

   glBindTexture(GL_TEXTURE_2D, image.id);
    glUseProgram(vertex.id);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  free(cube);
  free(camera);
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {

  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
  glfwSetWindowShouldClose(window,1);
  }
  Camera *camera = (Camera *)glfwGetWindowUserPointer(window);
  handleCameraMovement(window,key, camera);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}