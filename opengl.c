////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "game.h"
#include "sprite.h"

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
void opengl_create(int width, int height) {
  glOrtho(0, width, height, 0, -1, 1);
}

void opengl_load_sprite(sprite *sprite) {
  glTexImage2D(GL_TEXTURE_2D, 0, 4, sprite->width, sprite->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sprite->data);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_FLAT);
}

void opengl_draw_sprite(int x, int y, sprite *sprite) {
  opengl_load_sprite(sprite);

  // Clockwise starting in the upper left
  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x, y, 0.0);

    glTexCoord2f(0.0, 1.0);
    glVertex3f(x, y + sprite->height, 0.0);

    glTexCoord2f(1.0, 1.0);
    glVertex3f(x + sprite->width, y + sprite->height, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex3f(x + sprite->width, y, 0.0);

  glEnd();
}

void opengl_render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
