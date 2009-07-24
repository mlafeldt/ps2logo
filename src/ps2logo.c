/*
 * PS2 Logo Cryptor
 * (C) Copyright 2006 Mathias Lafeldt/Xope Systems
 *
 * NOTE: Most of this is based on the "ps2boot.txt" document by loser.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APP_NAME	"PS2 Logo Cryptor"
#define APP_VERSION	"1.0"

// Size of the PS2 logo in bytes
#define LOGO_SIZE	(12*2048) // 12 sectors x 2048 bytes

// Program's modes
enum {
	MODE_DECRYPT, // default
	MODE_ENCRYPT
};


/*
 * Displays the application's name and version, and a copyright notice.
 */
void ShowBanner(void)
{
	printf(APP_NAME" v"APP_VERSION"\n");
	printf("(C) 2006 M. Lafeldt/Xope Systems\n\n");
}

/*
 * Displays how to use the program.
 */
void ShowUsage(void)
{
	printf("Usage: ps2logo <input file> <output file> [-e key]\n");
	printf(" Decrypts/encrypts a sector dump of the PS2 logo.\n");
	printf(" Options are:\n");
	printf("  -e\tEncrypt logo with given key (hex byte) [0...FF]\n");
}

/*
 * Encrypts each pixel in the logo.
 *
 * args:	buffer with logo
 *		encryption key
 */
void EncryptLogo(unsigned char *logo, unsigned char key)
{
	int i;

	for (i = 0; i < LOGO_SIZE; i++)
		logo[i] = ((logo[i] << 5) | (logo[i] >> 3)) ^ key;
}

/*
 * Decrypts each pixel in the logo.
 *
 * args:	buffer with logo
 *		decryption key
 */
void DecryptLogo(unsigned char *logo, unsigned char key)
{
	int i;

	for (i = 0; i < LOGO_SIZE; i++) {
		logo[i] ^= key;
		logo[i] = (logo[i] << 3) | (logo[i] >> 5);
	}
}

int main(int argc, char *argv[])
{
	FILE *fp;
	unsigned char logo[LOGO_SIZE];
	int mode = MODE_DECRYPT;
	unsigned char key = 0;

	ShowBanner();

	// Check arguments
	if (argc < 3) {
		ShowUsage();
		return -1;
	}

	if ((argc == 5) && !strcmp(argv[3], "-e")) {
		sscanf(argv[4], "%02hhx", &key);
		mode = MODE_ENCRYPT;
	}

	// Open input file
	fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		fprintf(stderr, "Error: Can't open file '%s' for reading\n", argv[1]);
		return -2;
	}

	// Read logo from input file into buffer
	if (fread(logo, LOGO_SIZE, 1, fp) != LOGO_SIZE) {
		fclose(fp);
		return -3;
	}
	fclose(fp);

	// Open output file
	fp = fopen(argv[2], "wb");
	if (fp == NULL) {
		fprintf(stderr, "Error: Can't open file '%s' for writing\n", argv[2]);
		return -4;
	}

	// Decrypt/encrypt logo
	if (mode == MODE_DECRYPT) {
		// Due to the nature of the scheme it's very simple to get the decryption key.
		key = logo[0];
		printf("Decrypting logo (key = 0x%02X) ... ", key);
		DecryptLogo(logo, key);
	} else {
		printf("Encrypting logo (key = 0x%02X) ... ", key);
		EncryptLogo(logo, key);
	}

	// Write result to output file
	fwrite(logo, LOGO_SIZE, 1, fp);
	fclose(fp);

	printf("Done!\n");

	return 0;
}
