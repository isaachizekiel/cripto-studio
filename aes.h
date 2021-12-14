/* Header only AES attempt */

#ifndef AES_H
#define AES_H

#include "crypto-utils.h"
#include <inttypes.h>
#include <stdio.h>

#define BLOCK_LENGTH 16

unsigned char s_b[16][16]
    = { { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67,
          0x2b, 0xfe, 0xd7, 0xab, 0x76 },
        { 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2,
          0xaf, 0x9c, 0xa4, 0x72, 0xc0 },
        { 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5,
          0xf1, 0x71, 0xd8, 0x31, 0x15 },
        { 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80,
          0xe2, 0xeb, 0x27, 0xb2, 0x75 },
        { 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6,
          0xb3, 0x29, 0xe3, 0x2f, 0x84 },
        { 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe,
          0x39, 0x4a, 0x4c, 0x58, 0xcf },
        { 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02,
          0x7f, 0x50, 0x3c, 0x9f, 0xa8 },
        { 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda,
          0x21, 0x10, 0xff, 0xf3, 0xd2 },
        { 0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e,
          0x3d, 0x64, 0x5d, 0x19, 0x73 },
        { 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8,
          0x14, 0xde, 0x5e, 0x0b, 0xdb },
        { 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac,
          0x62, 0x91, 0x95, 0xe4, 0x79 },
        { 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4,
          0xea, 0x65, 0x7a, 0xae, 0x08 },
        { 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74,
          0x1f, 0x4b, 0xbd, 0x8b, 0x8a },
        { 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57,
          0xb9, 0x86, 0xc1, 0x1d, 0x9e },
        { 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87,
          0xe9, 0xce, 0x55, 0x28, 0xdf },
        { 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d,
          0x0f, 0xb0, 0x54, 0xbb, 0x16 } };

// for the convenience of our implementation
// we make this fied a 1-d array (1 x 16)
unsigned int gf[16] = { 0x02, 0x03, 0x01, 0x01, 0x01, 0x02, 0x03, 0x01,
                        0x01, 0x01, 0x02, 0x03, 0x03, 0x01, 0x01, 0x02 };

static void
aes_print (unsigned char *in, const char *label)
{
  printf ("%s", label);
  for (int i = 0; i < BLOCK_LENGTH; i++)
    {
      /* present it as a 4 x 4 matrix */
      if (i % 4 == 0)
        printf ("    ");
      printf ("%02x ", in[i]);
    }
  printf ("\n\n");
}

static void
aes_subs_bytes (unsigned char *in)
{
  unsigned char l, r;
  for (int i = 0; i < 16; i++)
    {
      l = (in[i] & 0xf0) >> 4;
      r = in[i] & 0x0f;
      in[i] = s_b[l][r];
    }
}

/* It is very important to note here that i choose
 * to represent the 4x4 array by 16 x 1 array
 * and at the basic leve shifting of rows is just
 * a series of swaping of array element */
static void
aes_shift_rows (unsigned char *in)
{
  /* Shift the first row by zero */

  /* Shift the second row by one */
  SWAP (in[1], in[13]);
  SWAP (in[1], in[5]);
  SWAP (in[5], in[9]);

  /* Shift the third row by two */
  SWAP (in[2], in[10]);
  SWAP (in[6], in[14]);

  /* Shift the fourth row by three */
  SWAP (in[3], in[15]);
  SWAP (in[7], in[15]);
  SWAP (in[11], in[15]);
}

/* this function uses a colomun by column matrix multiplication
 * it takes column between 0..3 and return the result at offset 0..3  */
static void
aes_mix_column (unsigned char *in, unsigned char off)
{
  unsigned char a;
  uint16_t b;
  unsigned char c[4] = { 0 };

  for (int i = 0, j = 0, k = 0; i < BLOCK_LENGTH; i++, j++)
    {
      // check if we start to calculate the column of the Galio's Field
      if (i % 4 == 0)
        {
          /* an index variable which is used along size offset
           * to access members of a column in the input array */
          j = 0;

          /* in[0] * gf[0] ^ in[1] * gf[4] ^ ... ^ in[3] * gf[12] holder */
          a = 0x00;

          /* in[0] * gf[0] holder.
           * incase of overflow i make it 16 byte wide */
          b = 0x0000;
        }

      /* Galio's Field multiplection begin */
      if (gf[i] == 3)
        {
          /* Galio's Field multiplication part */
          b = (in[j + off] * 2) ^ in[j + off];
        }
      else
        {
          /* Galio's Field multiplication part */
          b = in[j + off] * gf[i];
        }

      /* if there is an overflow */
      if (b >> 8)
        {
          b ^= 0x1b;
        }

      /* xor (in[y] * gf[x]) with the previous value */
      a ^= b;

      /* check if we finish xoring the matrix row and column result */
      if (j == 3)
        {
          /* save the final value in the array */
          c[k++] = a;
        }

      /* if we finished calculating the column of the matrix */
      if (i == 15)
        {
          /* put the final values at index + offset of
           * the same array we take in as input */
          in[0 + off] = c[0];
          in[1 + off] = c[1];
          in[2 + off] = c[2];
          in[3 + off] = c[3];
        }
    }
}

static void
aes_key_schedule (unsigned char *in)
{

  // rotate the last column
  SWAP (in[12], in[15]);
  SWAP (in[12], in[14]);
  SWAP (in[13], in[12]);

  // aes_subs_bytes();

  // aes_rotate_column();

  // aes_sub();

  // aes_derive()

  //
}

#endif
