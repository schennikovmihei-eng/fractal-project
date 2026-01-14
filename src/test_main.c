/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <assert.h>
#include "image.h"
#include "fractal.h"

static void test_image_creation(void)
{
        image_p img;
        
        printf("Testing image creation...\n");
        
        img = create_image(100, 100);
        assert(img != NULL);
        assert(img->width == 100);
        assert(img->height == 100);
        assert(img->data != NULL);
        
        set_pixel(img, 10, 10, 128);
        assert(get_pixel(img, 10, 10) == 128);
        
        free_image(img);
        printf("Image tests passed\n");
}

static void test_fractal_params(void)
{
        struct fractal_params params = {
                .xmin = -2.0,
                .xmax = 1.0,
                .ymin = -1.5,
                .ymax = 1.5,
                .max_iter = 100
        };
        
        printf("Testing fractal parameters...\n");
        
        assert(params.xmin < params.xmax);
        assert(params.ymin < params.ymax);
        assert(params.max_iter > 0);
        
        printf("Fractal parameter tests passed\n");
}

static void test_save_functions(void)
{
        image_p img = create_image(2, 2);
        
        printf("Testing save functions...\n");
        
        assert(img != NULL);
        
        set_pixel(img, 0, 0, 0);
        set_pixel(img, 1, 0, 85);
        set_pixel(img, 0, 1, 170);
        set_pixel(img, 1, 1, 255);
        
        assert(save_pgm(img, "test_ascii.pgm") == 0);
        
        assert(save_pgm_binary(img, "test_binary.pgm") == 0);
        
        free_image(img);
        printf("Save functions tests passed\n");
}

int main(void)
{
        printf("Running tests...\n");
        
        test_image_creation();
        test_fractal_params();
        test_save_functions();
        
        printf("Testing fractal generation...\n");
        image_p test_img = create_image(10, 10);
        if (test_img) {
                struct fractal_params test_params = {
                        .xmin = -2.0,
                        .xmax = 1.0,
                        .ymin = -1.5,
                        .ymax = 1.5,
                        .max_iter = 50
                };
                
                mandelbrot_fractal(test_img, &test_params);
                julia_fractal(test_img, -0.7, 0.27015, &test_params);
                free_image(test_img);
        }
        
        printf("All tests passed!\n");
        return 0;
}