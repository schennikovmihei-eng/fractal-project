#include "image.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

image_p create_image(pixel_coord width, pixel_coord height)
{
        image_p img;
        size_t data_size;
        
        assert(width > 0);
        assert(height > 0);
        
        img = malloc(sizeof(*img));
        assert(img != NULL);
        
        img->width = width;
        img->height = height;
        
        data_size = (size_t)width * height;
        assert(data_size <= SIZE_MAX / sizeof(pixel_data));
        
        img->data = malloc(data_size * sizeof(pixel_data));
        assert(img->data != NULL);
        
        memset(img->data, 0, data_size * sizeof(pixel_data));
        
        return img;
}

void free_image(image_p img)
{
        if (img == NULL)
                return;
        
        free(img->data);
        free(img);
}

pixel_data get_pixel(const_image_p picture, pixel_coord x, pixel_coord y)
{
        assert(picture != NULL);
        assert(x < picture->width);
        assert(y < picture->height);
        
        return picture->data[y * picture->width + x];
}

void set_pixel(image_p picture, pixel_coord x, pixel_coord y, pixel_data value)
{
        assert(picture != NULL);
        assert(x < picture->width);
        assert(y < picture->height);
        
        picture->data[y * picture->width + x] = value;
}

int save_pgm(const_image_p picture, const char *filename)
{
        FILE *to;
        pixel_coord i, j;
        
        assert(picture != NULL);
        assert(filename != NULL);
        
        to = fopen(filename, "w");
        if (to == NULL)
                return -1;
        
        fprintf(to, "P2\n%u %u\n255\n", picture->width, picture->height);
        
        for (j = 0; j < picture->height; ++j) {
                for (i = 0; i < picture->width; ++i) {
                        fprintf(to, "%u ", get_pixel(picture, i, j));
                }
                fprintf(to, "\n");
        }
        
        fclose(to);
        return 0;
}

int save_pgm_binary(const_image_p picture, const char *filename)
{
        FILE *to;
        
        assert(picture != NULL);
        assert(filename != NULL);
        
        to = fopen(filename, "wb");
        if (to == NULL)
                return -1;
        
        fprintf(to, "P5\n%u %u\n255\n", picture->width, picture->height);
        fwrite(picture->data, sizeof(pixel_data), 
               picture->width * picture->height, to);
        
        fclose(to);
        return 0;
}