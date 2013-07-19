/*
 * Copyright (C) 2006-2013 Mathias Lafeldt <mathias.lafeldt@gmail.com>
 *
 * This file is part of ps2logo, the PS2 logo decryptor.
 *
 * ps2logo is licensed under the terms of the MIT License. See LICENSE file.
 */

#include <stdio.h>
#include <stdlib.h>

/* Size of PS2 logo in bytes: 12 sectors x 2048 bytes */
#define LOGO_SIZE	(12 * 2048)


#if 0
static void encrypt_logo(unsigned char *logo, unsigned char key)
{
	int i;

	for (i = 0; i < LOGO_SIZE; i++)
		logo[i] = ((logo[i] << 5) | (logo[i] >> 3)) ^ key;
}
#endif

static void decrypt_logo(unsigned char *logo)
{
	unsigned char key = logo[0];
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

	if (argc < 3) {
		fprintf(stderr, "usage: %s <input file> <output file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		fprintf(stderr, "Error: could not open input file '%s'\n", argv[1]);
		return EXIT_FAILURE;
	}

	if (fread(logo, LOGO_SIZE, 1, fp) != 1) {
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

	decrypt_logo(logo);
	fwrite(logo, LOGO_SIZE, 1, fp);
	fclose(fp);

	return EXIT_SUCCESS;
}
