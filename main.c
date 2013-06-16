#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <stdio.h>

#define ESCAPE 27

int window;
void *sprite1;
void *sprite2;
void *sprite3;

void SetupGL(int width, int height) {
  glOrtho(0, width, height, 0, -1, 1);
}

void *CreateSprite(int width, int height, unsigned long color) {
  unsigned char *textureImage;

  // Allocate bytes
  textureImage = malloc(width*height*4);

  unsigned int i;
  for(i = 0; i < width * height * 4; i += 4) {
    textureImage[i] = color & 0xFF;
    textureImage[i+1] = (color >> 8) & 0xFF;
    textureImage[i+2] = (color >> 16) & 0xFF;
    textureImage[i+3] = (color >> 24) & 0xFF;
  }

  return textureImage;
}

void LoadImage(void *sprite, int width, int height) {
  glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sprite);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_FLAT);
}

void DrawSprite(int x, int y, int width, int height, void *sprite) {
  LoadImage(sprite, width, height);

  // Clockwise starting in the upper left
  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x, y, 0.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(x, y + height, 0.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(x + width, y + height, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(x + width, y, 0.0);

  glEnd();
}

void DrawGLScene()
{
  // Default is black
  //glClearColor(0.0f,0.1f,0.0f,0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  DrawSprite(0, 0, 128, 128, sprite1);
  DrawSprite(320-64, 240-64, 128, 128, sprite2);
  DrawSprite(640-128, 480-128, 128, 128, sprite3);

  glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y) 
{
  if (key == ESCAPE) {
    glutDestroyWindow(window);
    exit(0);
  }
}

int main(int argc, char **argv) {
  sprite1 = CreateSprite(128, 128, 0x000000FF);
  sprite2 = CreateSprite(128, 128, 0x0000FF00);
  sprite3 = CreateSprite(128, 128, 0x00FF0000);

  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(640, 480);  
  glutInitWindowPosition(0, 0);  
  window = glutCreateWindow("game");
  glutDisplayFunc(&DrawGLScene);  
  glutKeyboardFunc(&keyPressed);
  SetupGL(640, 480);
  glutMainLoop();  
  return 0;
}
