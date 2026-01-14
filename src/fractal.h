#ifndef FRACTAL_H
#define FRACTAL_H

#include "image.h"

struct fractal_params {
        double xmin;
        double xmax;
        double ymin;
        double ymax;
        int max_iter;
};

void mandelbrot_fractal(image_p picture, const struct fractal_params *params);
void julia_fractal(image_p picture, double cx, double cy, 
                   const struct fractal_params *params);

#endif /* FRACTAL_H */