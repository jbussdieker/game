////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include "sprite.h"

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
sprite *sprite_create(int width, int height, unsigned long color) {
  sprite *sprite = malloc(sizeof(sprite));
  sprite->width = width;
  sprite->height = height;
  sprite->data = malloc(width*height*4);

  unsigned int i;
  unsigned char *data = sprite->data;
  for(i = 0; i < width * height * 4; i += 4) {
    data[i] = color & 0xFF;
    data[i+1] = (color >> 8) & 0xFF;
    data[i+2] = (color >> 16) & 0xFF;
    data[i+3] = (color >> 24) & 0xFF;
  }

  return sprite;
}

void sprite_delete(sprite *sprite) {
  free(sprite->data);
  free(sprite);
}
