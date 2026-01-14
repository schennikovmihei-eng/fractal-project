#include "fractal.h"
#include "image.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  image_p img;
  struct fractal_params params = {
      .xmin = -2.0, .xmax = 1.0, .ymin = -1.5, .ymax = 1.5, .max_iter = 1000};

  img = create_image(800, 600);
  assert(img != NULL);

  printf("Generating Mandelbrot fractal...\n");
  mandelbrot_fractal(img, &params);

  if (save_pgm_binary(img, "mandelbrot.pgm") == 0) {
    printf("Saved to mandelbrot.pgm (binary P5)\n");
  }

  if (save_pgm(img, "mandelbrot_ascii.pgm") == 0) {
    printf("Saved to mandelbrot_ascii.pgm (ASCII P2)\n");
  }

  julia_fractal(img, -0.7, 0.27015, &params);
  save_pgm_binary(img, "julia.pgm");
  printf("Saved to julia.pgm\n");

  free_image(img);

  return 0;
}