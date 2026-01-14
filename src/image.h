#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdio.h>

typedef uint32_t pixel_coord;
typedef uint8_t pixel_data;

struct image {
  pixel_coord width;
  pixel_coord height;
  pixel_data *data;
};

typedef struct image *image_p;
typedef const struct image *const_image_p;

image_p create_image(pixel_coord width, pixel_coord height);
void free_image(image_p img);

pixel_data get_pixel(const_image_p picture, pixel_coord x, pixel_coord y);
void set_pixel(image_p picture, pixel_coord x, pixel_coord y, pixel_data value);

int save_pgm(const_image_p picture, const char *filename);
int save_pgm_binary(const_image_p picture, const char *filename);

#endif