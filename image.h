#pragma once
#include "stb_image.h"
#include "glad.h"
typedef struct Image
{
     int width;
     int height;
    unsigned int nrChannels;
    unsigned int id;

} Image;


void loadImage(const char* imagePath, Image *image){
     glGenTextures(1,  &image->id);
  glBindTexture(GL_TEXTURE_2D,
                image->id); // all upcoming GL_TEXTURE_2D operations now have
                          // effect on this texture object
  // set the texture wrapping parameters
  glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
      GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  // The FileSystem::getPath(...) is part of the GitHub repository so we can
  // find files on any IDE/platform; replace it with your own image path.
  unsigned char *data =
      stbi_load(imagePath,&image->width, &image->height, &image->nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width,image->height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    printf("cannot load\n");
  }
  stbi_image_free(data);



}
