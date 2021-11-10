#ifndef AES_H
#define AES_H


/* debug functions  */
void aes_print_4_4_x(void *in0);

void aes_print_4_4_y(void *in0);


/* premitive functions  */
void aes_shift_by(void *in, unsigned char axis, unsigned char amount);

void aes_subs_byte(void *in, unsigned char i, unsigned char j);



void aes_mix_column(void *in);


#endif
