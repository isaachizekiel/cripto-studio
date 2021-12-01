# crypto-studio

Hi!, This repository is where i put my occasional cryptographic fascinations in order to understand the internal workings of a cryptographic algorithms.


# AES-128 

The main goal for of this challenge is to implement aes-128 with not nested loops. for example I represent 4 x 4 matrix as 1 x 16 array.


[/aes.h](https://github.com/isaachizekiel/crypto-studio/blob/main/aes.h) a header only AES-128 implementation

[/aes-test.c](https://github.com/isaachizekiel/crypto-studio/blob/main/aes-test.c) a test utility for the [/aes.h](https://github.com/isaachizekiel/crypto-studio/blob/main/aes.h)

[/crypto-utils.h](https://github.com/isaachizekiel/crypto-studio/blob/main/crypto-utils.h) home for general cryptographic operations

the results can be verified at [NIST- ADVANCED ENCRYPTION STANDARD](https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.197.pdf) by the matrices at page 33 of of the second row.


TODO: implement `static void aes_key_schedule(unsigned char *in);`
