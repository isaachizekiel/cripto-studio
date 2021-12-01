#include "aes.h"

int
main()
{
  /* The initial key that is used to generate all round keys */
  unsigned char key[16] = {
    0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d,
    0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34
  };

  /* The message that we are going to Encrypt */
  unsigned char msg[16] = {
    0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
  };

  aes_print(key, "key");

  aes_print(msg, "msg");
  
  for (int i = 0; i < 16; i++)
    {
      msg[i] ^= key[i];
    }

  // printing the begining of the state
  aes_print(msg, "exp");


  // byte by byte substitution
  aes_subs_bytes(msg);

  // printing the state of the cipher
  aes_print(msg, "sub");


  aes_shift_rows(msg);
  
  // printing the state of the cipher
  aes_print(msg, "shf");

  // TODO: comment
  aes_mix_column(msg, 0);
  aes_mix_column(msg, 4);
  aes_mix_column(msg, 8);
  aes_mix_column(msg, 12);

  // printing mix column
  aes_print(msg, "mix");
  
  return 0;
  
}
