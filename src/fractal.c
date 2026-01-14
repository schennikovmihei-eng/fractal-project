#include "fractal.h"
#include <assert.h>
#include <math.h>

static int compute_mandelbrot(double x0, double y0, int max_iter) {
  double x = 0.0;
  double y = 0.0;
  double x2 = 0.0;
  double y2 = 0.0;
  int iteration = 0;

  assert(max_iter > 0);

  while (x2 + y2 <= 4.0 && iteration < max_iter) {
    y = 2 * x * y + y0;
    x = x2 - y2 + x0;
    x2 = x * x;
    y2 = y * y;
    iteration++;
  }

  return iteration;
}

void mandelbrot_fractal(image_p picture, const struct fractal_params *params) {
  pixel_coord px, py;
  double x0, y0;

  assert(picture != NULL);
  assert(params != NULL);
  assert(params->xmin < params->xmax);
  assert(params->ymin < params->ymax);
  assert(params->max_iter > 0);

  for (py = 0; py < picture->height; ++py) {
    for (px = 0; px < picture->width; ++px) {
      x0 = params->xmin + (params->xmax - params->xmin) * px / picture->width;
      y0 = params->ymin + (params->ymax - params->ymin) * py / picture->height;

      int iter = compute_mandelbrot(x0, y0, params->max_iter);
      pixel_data color = (255 * iter) / params->max_iter;
      set_pixel(picture, px, py, color);
    }
  }
}

void julia_fractal(image_p picture, double cx, double cy,
                   const struct fractal_params *params) {
  pixel_coord px, py;
  double x0, y0;

  assert(picture != NULL);
  assert(params != NULL);
  assert(!isnan(cx) && !isnan(cy));
  assert(params->xmin < params->xmax);
  assert(params->ymin < params->ymax);
  assert(params->max_iter > 0);

  for (py = 0; py < picture->height; ++py) {
    for (px = 0; px < picture->width; ++px) {
      x0 = params->xmin + (params->xmax - params->xmin) * px / picture->width;
      y0 = params->ymin + (params->ymax - params->ymin) * py / picture->height;

      double x = x0;
      double y = y0;
      int iteration = 0;

      while (x * x + y * y <= 4.0 && iteration < params->max_iter) {
        double x_temp = x * x - y * y + cx;
        y = 2 * x * y + cy;
        x = x_temp;
        iteration++;
      }

      pixel_data color = (255 * iteration) / params->max_iter;
      set_pixel(picture, px, py, color);
    }
  }
}