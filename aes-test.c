#include <stdio.h>
#include "aes.h"

int
main()
{


  unsigned char k[16] = {
    0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d,
    0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34
  };
  
  unsigned char m[16] = {
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
  };


  /*
    void aes_print_4_4_x(void *in0);

    void aes_print_4_4_y(void *in0);

    void aes_shift_by(void *in, unsigned char axis, unsigned char amount);

    void aes_subs_byte(void *in, unsigned char i, unsigned char j);
   */


  aes_print_4_4_y(k);
  printf("\n");
  
  aes_print_4_4_y(m);
  printf("\n");
  
  // subs bytes
  for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
	{
	  aes_subs_byte(m, i, j);
	}

    }
  aes_print_4_4_y(m);
  printf("\n");


  aes_shift_by(m, 1, 1);
  aes_shift_by(m, 1, 2);
  aes_shift_by(m, 1, 3);
  
  aes_print_4_4_y(m);
  printf("\n");


  aes_mix_column(m);
  aes_print_4_4_y(m);
  
  printf("\n");
    
  
  
  return 0;
}
