#include "seamcarving.h"
#include <stdlib.h>
#include <math.h>

static int idx(int y, int x, int width) {
    return y * width + x;
}

void calc_energy(struct rgb_img *im, struct rgb_img **grad) {
    int height = (int)im->height;
    int width = (int)im->width;

    create_img(grad, im->height, im->width);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int left = (x == 0) ? width - 1 : x - 1;
            int right = (x == width - 1) ? 0 : x + 1;
            int up = (y == 0) ? height - 1 : y - 1;
            int down = (y == height - 1) ? 0 : y + 1;

            int rx = (int)get_pixel(im, y, right, 0) - (int)get_pixel(im, y, left, 0);
            int gx = (int)get_pixel(im, y, right, 1) - (int)get_pixel(im, y, left, 1);
            int bx = (int)get_pixel(im, y, right, 2) - (int)get_pixel(im, y, left, 2);

            int ry = (int)get_pixel(im, down, x, 0) - (int)get_pixel(im, up, x, 0);
            int gy = (int)get_pixel(im, down, x, 1) - (int)get_pixel(im, up, x, 1);
            int by = (int)get_pixel(im, down, x, 2) - (int)get_pixel(im, up, x, 2);

            double dx2 = (double)(rx * rx + gx * gx + bx * bx);
            double dy2 = (double)(ry * ry + gy * gy + by * by);

            uint8_t energy = (uint8_t)(sqrt(dx2 + dy2) / 10.0);
            set_pixel(*grad, y, x, energy, energy, energy);
        }
    }
}

void dynamic_seam(struct rgb_img *grad, double **best_arr) {
    int height = (int)grad->height;
    int width = (int)grad->width;

    *best_arr = (double *)malloc(height * width * sizeof(double));

    for (int x = 0; x < width; x++) {
        (*best_arr)[idx(0, x, width)] = (double)get_pixel(grad, 0, x, 0);
    }

    for (int y = 1; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double best_prev = (*best_arr)[idx(y - 1, x, width)];

            if (x > 0 && (*best_arr)[idx(y - 1, x - 1, width)] < best_prev) {
                best_prev = (*best_arr)[idx(y - 1, x - 1, width)];
            }

            if (x < width - 1 && (*best_arr)[idx(y - 1, x + 1, width)] < best_prev) {
                best_prev = (*best_arr)[idx(y - 1, x + 1, width)];
            }

            (*best_arr)[idx(y, x, width)] = (double)get_pixel(grad, y, x, 0) + best_prev;
        }
    }
}

void recover_path(double *best, int height, int width, int **path) {
    *path = (int *)malloc(height * sizeof(int));

    int min_col = 0;
    for (int x = 1; x < width; x++) {
        if (best[idx(height - 1, x, width)] < best[idx(height - 1, min_col, width)]) {
            min_col = x;
        }
    }
    (*path)[height - 1] = min_col;

    for (int y = height - 2; y >= 0; y--) {
        int below = (*path)[y + 1];

        int best_col = below;
        double best_val = best[idx(y, below, width)];

        if (below > 0) {
            double left_val = best[idx(y, below - 1, width)];
            if (left_val < best_val || (left_val == best_val && (below - 1) < best_col)) {
                best_val = left_val;
                best_col = below - 1;
            }
        }

        if (below < width - 1) {
            double right_val = best[idx(y, below + 1, width)];
            if (right_val < best_val || (right_val == best_val && (below + 1) < best_col)) {
                best_val = right_val;
                best_col = below + 1;
            }
        }

        (*path)[y] = best_col;
    }
}

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path) {
    int height = (int)src->height;
    int width = (int)src->width;

    create_img(dest, src->height, src->width - 1);

    for (int y = 0; y < height; y++) {
        int new_x = 0;
        for (int x = 0; x < width; x++) {
            if (x != path[y]) {
                int r = get_pixel(src, y, x, 0);
                int g = get_pixel(src, y, x, 1);
                int b = get_pixel(src, y, x, 2);
                set_pixel(*dest, y, new_x, r, g, b);
                new_x++;
            }
        }
    }
}