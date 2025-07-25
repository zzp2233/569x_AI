/*
 * lfs util functions
 *
 * Copyright (c) 2017, Arm Limited. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "lfs_util.h"

// Only compile if user does not provide custom config
#ifndef LFS_CONFIG


// Software CRC implementation with small lookup table
uint32_t lfs_crc(uint32_t crc, const void *buffer, size_t size)
{
    static const uint32_t rtable[16] =
    {
        0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
        0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
        0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
        0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c,
    };

    const uint8_t *data = buffer;

    for (size_t i = 0; i < size; i++)
    {
        crc = (crc >> 4) ^ rtable[(crc ^ (data[i] >> 0)) & 0xf];
        crc = (crc >> 4) ^ rtable[(crc ^ (data[i] >> 4)) & 0xf];
    }

    return crc;
}
// zzn add 2024/03/27
char *strchr(const char *str, int c)
{
    while (*str != '\0')
    {
        if (*str == (char)c)
        {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}
size_t strspn(const char *str1, const char *str2)
{
    size_t count = 0;
    while (*str1 && strchr(str2, *str1))
    {
        str1++;
        count++;
    }
    return count;
}
size_t strcspn(const char *str1, const char *str2)
{
    size_t count = 0;
    while(*str1 && !strchr(str2, *str1))
    {
        str1++;
        count++;
    }
    return count;
}
// zzn add 2024/03/27

#endif
