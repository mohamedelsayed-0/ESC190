#include <stdio.h>
#include "c_img.h"

static uint8_t clamp_channel(double value)
{
    if (value < 0.0)
    {
        return 0;
    }
    if (value > 255.0)
    {
        return 255;
    }
    return (uint8_t)(value + 0.5);
}

static void adjust_brightness(struct rgb_img *src, struct rgb_img **dest, double factor)
{
    size_t y;
    size_t x;

    create_img(dest, src->height, src->width);

    for (y = 0; y < src->height; y++)
    {
        for (x = 0; x < src->width; x++)
        {
            uint8_t r = get_pixel(src, (int)y, (int)x, 0);
            uint8_t g = get_pixel(src, (int)y, (int)x, 1);
            uint8_t b = get_pixel(src, (int)y, (int)x, 2);

            set_pixel(*dest, (int)y, (int)x,
                      clamp_channel(r * factor),
                      clamp_channel(g * factor),
                      clamp_channel(b * factor));
        }
    }
}

int main(void)
{
    struct rgb_img *original = NULL;
    struct rgb_img *adjusted = NULL;

    double brightness_levels[5] = {0.4, 0.7, 1.0, 1.3, 1.6};
    char *output_files[5] = {
        "cannon_brightness_1.bin",
        "cannon_brightness_2.bin",
        "cannon_brightness_3.bin",
        "cannon_brightness_4.bin",
        "cannon_brightness_5.bin"
    };

    int i;

    read_in_img(&original, "image.bin");

    for (i = 0; i < 5; i++)
    {
        adjust_brightness(original, &adjusted, brightness_levels[i]);
        write_img(adjusted, output_files[i]);
        destroy_image(adjusted);
        adjusted = NULL;
    }

    destroy_image(original);

    printf("Created 5 brightness-adjusted images.\n");
    return 0;
}
