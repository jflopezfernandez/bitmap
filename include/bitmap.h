/**
 * This file contains the structure definitions required to
 * generate a bitmap file.
 *
 * @author Jose Fernando Lopez Fernandez
 * @copyright GNU General Public License v. 3
 *
 * @file bitmap.h
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
typedef struct {
    
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
typedef struct {

    /**
     * The size of this structure.
     *
     */
    int32_t struct_size;

    /**
     * The width of the bitmap image, in pixels.
     *
     */
    int32_t width;

    /**
     * The height of the bitmap image, in pixels.
     *
     */
    int32_t height;

    /**
     * Number of planes for the target device.
     *
     * @details
     * According to the Windows documentation, this value
     * represents the number of planes for the target
     * device. However, it must also always be set to 1, so
     * the value of this element is questionable.
     *
     */
    int16_t planes;

    /**
     * The number of bits per pixel.
     *
     * @details This value effectively determines the number
     * of possible colors in the bitmap, as calculated by
     * (bit_count * R) + (bit_count * G) + (bit_count * B).
     * The current version of this application always uses a
     * bit count of 24 per pixel.
     *
     */
    int16_t bit_count;

    /**
     * The type of compression for this bitmap.
     *
     * @details While bitmaps can actually be JPEG or PNG
     * encoded, the current version of this application
     * simply uses plain, uncompressed bitmaps.
     *
     */
    int32_t compression;

    /**
     * The size of the actual bitmap image data.
     *
     * @details Unlike the size element in the bitmap file
     * header struct, this element defines the size of the
     * actual image data in this file.
     *
     */
    int32_t image_size;

    /**
     * The image's horizontal resolution in pixels-per-meter
     * (PPM).
     *
     */
    int32_t x_ppm;

    /**
     * The image's vertical resolution in pixels-per-meter
     * (PPM).
     *
     */
    int32_t y_ppm;

    /**
     * The number of color indexes used by the bitmap image.
     *
     */
    int32_t color_indexes_used;

    /**
     * The number of color indexes that are absolutely
     * required for displaying the image.
     *
     */
    int32_t color_indexes_reqd;
} bitmap_info_header_t;

#endif /** PROJECT_INCLUDES_BITMAP_H */
