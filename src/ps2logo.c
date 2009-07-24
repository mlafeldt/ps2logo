/*
 * PS2 Logo Cryptor - decrypt/encrypt a sector dump of the PS2 logo
 * (C) Copyright 2006 Mathias Lafeldt/Xope Systems
 *
 * NOTE: Most of this is based on the "ps2boot.txt" document by loser.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APP_NAME	"PS2 Logo Cryptor"
#define APP_VERSION	"1.1"

/* Size of PS2 logo in bytes: 12 sectors x 2048 bytes */
#define LOGO_SIZE	(12*2048)

/* Static encryption key */
#define ENC_KEY		0xA4


static void encrypt_logo(unsigned char *logo, unsigned char key)
{
	int i;

	for (i = 0; i < LOGO_SIZE; i++)
		logo[i] = ((logo[i] << 5) | (logo[i] >> 3)) ^ key;
}

static void decrypt_logo(unsigned char *logo, unsigned char key)
{
	int i;

	for (i = 0; i < LOGO_SIZE; i++) {
		logo[i] ^= key;
		logo[i] = (logo[i] << 3) | (logo[i] >> 5);
	}
}

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	unsigned char logo[LOGO_SIZE];
	unsigned char key;

	if (argc < 3) {
		fprintf(stderr, "usage: %s <input file> <output file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		fprintf(stderr, "Error: could not open input file '%s'\n", argv[1]);
		return EXIT_FAILURE;
	}

	if (fread(logo, LOGO_SIZE, 1, fp) != LOGO_SIZE) {
		fprintf(stderr, "Error: could not read logo from input file\n");
		fclose(fp);
		return EXIT_FAILURE;
	}

	fclose(fp);
	fp = fopen(argv[2], "wb");
	if (fp == NULL) {
		fprintf(stderr, "Error: could not open output file '%s'\n", argv[2]);
		return EXIT_FAILURE;
	}

	if (*(unsigned int*)logo != 0x00000000) {
		key = logo[0];
		printf("Decrypting logo with key 0x%02x ... ", key);
		decrypt_logo(logo, key);
	} else {
		key = ENC_KEY;
		printf("Encrypting logo with key 0x%02x ... ", key);
		encrypt_logo(logo, key);
	}

	fwrite(logo, LOGO_SIZE, 1, fp);
	fclose(fp);

	printf("done.\n");

	return EXIT_SUCCESS;
}
