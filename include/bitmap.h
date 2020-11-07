/*
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
 *
 */

#ifndef PROJECT_INCLUDES_BITMAP_H
#define PROJECT_INCLUDES_BITMAP_H

/**
 * Structure describing the bitmap file header.
 *
 * @struct bitmap_file_header_t
 *
 */
typedef struct bitmap_file_header_t {
    
    /**
     * The magic number identifying the generated output as
     * a Windows bitmap file.
     *
     * @details The magic number must be set to the two
     * characters 'B' and 'M'. In hexadecimal, this is equal
     * to 0x424D.
     *
     */
    char magic_number[2];

    /**
     * The total size, in bytes, of the generated bitmap
     * file.
     *
     */
    int32_t file_size;

    /**
     * As per the Windows documentation, this value is
     * reserved and should always be zero.
     *
     */
    int16_t reserved_1;

    /**
     * As per the Windows documentation, this value is
     * reserved and should always be set to zero.
     *
     */
    int16_t reserved_2;

    /**
     * The size of the offset, in bytes, from the start of
     * the file to the beginning of the actual image data.
     *
     */
    int32_t offset_bits;

} bitmap_file_header_t;

/**
 * @struct bitmap_info_header_t
 * @brief Structure describing the bitmap image information
 * header.
 *
 */
typedef struct bitmap_info_header_t {
    int32_t struct_size;
    int32_t width;
    int32_t height;
    int16_t planes;
    int16_t bit_count;
    int32_t compression;
    int32_t image_size;
    int32_t x_ppm;
    int32_t y_ppm;
    int32_t color_indexes_used;
    int32_t color_indexes_reqd;
} bitmap_info_header_t;

#endif /** PROJECT_INCLUDES_BITMAP_H */
