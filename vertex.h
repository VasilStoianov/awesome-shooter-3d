#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "glad.h"
#include "GLFW/glfw3.h"
#include "math/mat4.h"

typedef struct Vertex{
 int id;
} Vertex;


Vertex createVertex(char *filePath){
    char* fileWi;
   strcpy(fileWi,filePath);
   strcat(fileWi,"vertex.vs");
   
   
   FILE *file = fopen(fileWi,"r");
   if(file == NULL){
    printf("ERROR: Cannot open shader FILE!\n");
   }

    fseek(file,0,SEEK_END);
    int end = ftell(file);
    rewind(file);

    char  *source = (char*)malloc(end+1);
    if(source == NULL)printf("ERROR: Cannot allocate memory for shader source!\n");


    fread(source,1,end,file);
    
    source[end] = '\0';
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,(const char**)&source,NULL);
    glCompileShader(vertexShader);
  int success;
  char infoLog[512];

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("%s \n", infoLog);
  }
    fclose(file);
    printf("INF: File closed!\n");
    memset(&fileWi,0,sizeof(fileWi));
    fileWi = strcat(filePath,"fragment.fs");
    
    file = fopen(fileWi,"r");
     
     if(file ==NULL) printf("ERROR: Cannot open file!\n");
    fseek(file,0,SEEK_END);

    end = ftell(file);
    rewind(file);
    source = (char*)malloc(end+1);

    fread(source,1,end,file);

    source[end] = '\0';
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,(const char**)&source,NULL);
    glCompileShader(fragmentShader);
glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("%s \n", infoLog);
  }
    Vertex vertex = {0};
    vertex.id = glCreateProgram();
    glAttachShader(vertex.id,vertexShader);
    glAttachShader(vertex.id,fragmentShader);
    glLinkProgram(vertex.id);

    
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
    free(source);
    fclose(file);
  return vertex;
}


void setUniformMatrix4f(char* uniName, int programId, mat4f matrix){

    int matrixTranslate = glGetUniformLocation(programId,uniName);
    glUseProgram(programId);
    glUniformMatrix4fv(matrixTranslate,1,GL_TRUE,*matrix);
}


