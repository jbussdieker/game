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

void LoadImage() {
  int width = 32;
  int height = 32;
  GLubyte *textureImage;

  // Allocate bytes
  textureImage = malloc(width*height*3);

  // Clear to black
  memset(textureImage, 0, width*height*3);

  // Upper right (blue)
  textureImage[width*height*3-1] = 255;

  // Center (green)
  textureImage[width*height*3/2+width*3/2+1] = 255;

  // Bottom left (red)
  textureImage[0] = 255;

  glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_FLAT);
}

void DrawGLScene()
{
  glClearColor(0.0f,0.1f,0.0f,0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Clockwise starting in the upper left
  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.5, 0.5, 0.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.5, 0.5, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5, -0.5, 0.0);

  glEnd();

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
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(640, 480);  
  glutInitWindowPosition(0, 0);  
  window = glutCreateWindow("game");
  glutDisplayFunc(&DrawGLScene);  
  glutKeyboardFunc(&keyPressed);
  LoadImage();
  glutMainLoop();  
  return 0;
}
