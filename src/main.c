/*
 * @copyright {
 * Bitmap - Image generation utility
 * Copyright (C) 2020 Jose Fernando Lopez Fernandez
 * 
 * This program is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <https://www.gnu.org/licenses/>.
 * }
 *
 */

#pragma pack(1)

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#include "bitmap.h"

typedef struct rgb_t {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgb_t;

int main(int argc, char *argv[])
{
    if (argc == 1) {
        fprintf(stderr, "[Error] No input(s).\n");
        return EXIT_FAILURE;
    }

    bitmap_info_header_t info_header;
    info_header.struct_size = 40;
    info_header.width = 1050;
    info_header.height = 600;
    info_header.planes = 1;
    info_header.bit_count = 24;
    info_header.compression = 0;
    info_header.image_size = info_header.width * info_header.height * ((sizeof (rgb_t)));
    info_header.x_ppm = 11811;
    info_header.y_ppm = 11811;
    info_header.color_indexes_used = 0;
    info_header.color_indexes_reqd = 0;

    bitmap_file_header_t file_header;
    file_header.magic_number[0] = 'B';
    file_header.magic_number[1] = 'M';
    file_header.file_size = info_header.image_size + sizeof (bitmap_file_header_t);
    file_header.reserved_1 = 0;
    file_header.reserved_2 = 0;
    file_header.offset_bits = 54;

    const char* filename = argv[argc - 1];

    FILE* output_file = fopen(filename, "w");

    if (output_file == NULL) {
        fprintf(stderr, "[Error] Could not create output file: %s\n", filename);
        return EXIT_FAILURE;
    }

    fwrite(&file_header, sizeof (file_header), 1, output_file);
    fwrite(&info_header, sizeof (info_header), 1, output_file);

    rgb_t color;
    color.red   = 0xFF;
    color.green = 0xFF;
    color.blue  = 0xFF;

    for (int i = 0; i < info_header.height; ++i) {
        for (int j = 0; j < info_header.width; ++j) {
            fwrite(&color, sizeof (color), 1, output_file);
        }
    }

    fclose(output_file);

    return EXIT_SUCCESS;
}
