#pragma once
#include <stdio.h>
#include "vector.h"
#include "math.h"


# define M_PI		3.14159265358979323846	/* pi */
#define toRad(x) (x*M_PI/180.f)
typedef float mat4f[4][4];


void printMatix(mat4f matrix){
for(int x =0; x<4; x++){
 for(int j=0; j<4; j++){
  printf("%f ,", matrix[x][j]);
 }
  printf("\n");
}
}

void mat4( float num,mat4f *matrix)
{

    for(int x = 0; x<4;x++){
       (*matrix)[x][x] = num;
    }

}



void identity(mat4f* m){

	(*m)[0][0] = (*m)[1][1] = (*m)[2][2] = (*m)[3][3] = 1.0f;
}

void multiplyMat4f2(mat4f result,  mat4f mat1, mat4f mat2)
{

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void multiplyMat4f(mat4f dest, mat4f m)
{


 mat4f result = {0}; // Temporary matrix to store results

    // Perform matrix multiplication
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Compute the dot product of the i-th row of `dest` with the j-th column of `src`
       result[i][j] = m[i][0] * m[0][j] +
                              m[i][1] * m[1][j] +
                              m[i][2] * m[2][j] +
                              m[i][3] * m[3][j];
        }
    }

    // Copy the result back into `dest` to modify the original matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dest[i][j] = result[i][j];
        }
    }
}
void setTranslation(vector vec,mat4f matrix)
{
   matrix[0][3]=vec.x;
    matrix[1][3]=vec.y;
   matrix[2][3]=vec.z;
}



void setForwards(vector forwards,mat4f *matrix){
  (*matrix)[0][0] = forwards.x;
  (*matrix)[0][1] = forwards.y;
  (*matrix)[0][2] = forwards.z;
}

void setUp(vector up,mat4f *matrix){
  (*matrix)[1][0] = up.x;
  (*matrix)[1][1] = up.y;
  (*matrix)[1][2] = up.z;
}

void setRight(vector right,mat4f *matrix){
  (*matrix)[2][0] = right.x;
  (*matrix)[2][1] = right.y;
  (*matrix)[2][2] = right.z;
}

void setPosition(vector pos,mat4f *matrix){
  (*matrix)[3][0] = pos.x;
  (*matrix)[3][1] = pos.y;
  (*matrix)[3][2] = pos.z;
}


void mat4fFromVectors(mat4f *matrix, vector up, vector right,vector forwards,vector position){
  setForwards(forwards,matrix);
  setUp(up,matrix);
  setRight(right,matrix);
  setPosition(position,matrix);


	(*matrix)[0][3] = 0;
	(*matrix)[1][3] = 0;
	(*matrix)[2][3] = 0;
	(*matrix)[3][3] = 1;

}


void setRotation(mat4f *matrix, float angle) {
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    
    (*matrix)[0][0] = cosAngle;
    (*matrix)[0][2] = sinAngle;
    (*matrix)[2][0] = -sinAngle;
    (*matrix)[2][2] = cosAngle;
}


void setScale(vector scale, mat4f *matrix){
  identity(matrix);
    
    (*matrix)[0][0]=scale.x;
    (*matrix)[1][1]=scale.y;
    (*matrix)[2][2]=scale.z;
}



void createProjection(float fov,mat4f* m){
  float tang = tanf(toRad(fov/2.f));
 
  printf("%f ",tan(toRad(fov/2.f)));
 
  float f = 1/tang;

  identity(m);

 (*m)[0][0] =f;
  (*m)[1][1] = f;
  (*m)[3][3]=0.0;
  (*m)[3][2] = 1.f;    

}

void setRotationY(float angle, mat4f matrix){
	
   float cosA = cosf(angle);
    float sinA = sinf(angle);

    matrix[0][0] = cosA;  matrix[0][1] = 0.0f; matrix[0][2] = sinA;  matrix[0][3] = 0.0f;
    matrix[1][0] = 0.0f;  matrix[1][1] = 1.0f; matrix[1][2] = 0.0f;  matrix[1][3] = 0.0f;
    matrix[2][0] = -sinA; matrix[2][1] = 0.0f; matrix[2][2] = cosA;  matrix[2][3] = 0.0f;
    matrix[3][0] = 0.0f;  matrix[3][1] = 0.0f; matrix[3][2] = 0.0f;  matrix[3][3] = 1.0f;
}

void setRotationX(float angle, mat4f matrix){
   float cosA = cosf(angle);
    float sinA = sinf(angle);

    matrix[0][0] = 1.0f; matrix[0][1] = 0.0f;  matrix[0][2] = 0.0f;  matrix[0][3] = 0.0f;
    matrix[1][0] = 0.0f; matrix[1][1] = cosA; matrix[1][2] = -sinA; matrix[1][3] = 0.0f;
    matrix[2][0] = 0.0f; matrix[2][1] = sinA; matrix[2][2] = cosA;  matrix[2][3] = 0.0f;
    matrix[3][0] = 0.0f; matrix[3][1] = 0.0f;  matrix[3][2] = 0.0f;  matrix[3][3] = 1.0f;
}

void setRotationZ(float angle, mat4f m){

		float c = cos(angle*M_PI/180);
	float s = sin(angle*M_PI/180);
  m[0][1] = c;
  m[1][1] = s;
  m[0][2] = -s;
  m[1][2] = c; 
}




void transform(mat4f res,mat4f translate,mat4f rotate,mat4f scale){
    mat4f temp;
    identity(&temp);
    multiplyMat4f2(temp,rotate,scale);
    printf("--  printinf TEMP FIST MULTI-----------------------\n");
    printMatix(temp);
    printf("====================");
    multiplyMat4f2(res,translate,temp);

printf("--  printinf TEMP LASTMULTI-----------------------\n");
}