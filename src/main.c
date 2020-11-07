/**
 * This file contains the entry point of the bitmap program.
 *
 * @author Jose Fernando Lopez Fernandez
 * @copyright GNU General Public License v. 3
 *
 * @file main.c
 *
 */

#pragma pack(1)

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
    info_header.struct_size = sizeof (bitmap_info_header_t);
    // info_header.width = 1050;
    // info_header.height = 600;
    info_header.width = 50;
    info_header.height = 50;
    info_header.planes = 1;
    info_header.bit_count = 24;
    info_header.compression = 0;
    info_header.image_size = info_header.width * info_header.height * ((sizeof (rgb_t))) + (info_header.height * 2);
    info_header.x_ppm = 11811;
    info_header.y_ppm = 11811;
    info_header.color_indexes_used = 0;
    info_header.color_indexes_reqd = 0;

    assert(40 == sizeof (bitmap_info_header_t));

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

    rgb_t color_white;
    color_white.red   = 0xFF;
    color_white.green = 0xFF;
    color_white.blue  = 0xFF;

    rgb_t color_black;
    color_black.red = 0x00;
    color_black.green = 0x00;
    color_black.blue = 0x00;

    rgb_t* color = NULL;

    uint8_t null_byte = 0x00;

    for (int i = 0; i < info_header.height; ++i) {
        for (int j = 0; j < info_header.width; ++j) {
            color = ((i == 24) && (j == 24)) ? &color_black : &color_white;
            fwrite(color, sizeof (rgb_t), 1, output_file);

            if ((j + 1) == info_header.width) {
                fwrite(&null_byte, sizeof (null_byte), 2, output_file);
            }
        }
    }

    fclose(output_file);

    return EXIT_SUCCESS;
}
