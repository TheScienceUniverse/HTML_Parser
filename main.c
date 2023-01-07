#include "./lib/parser.h"

int main (int argc, char *argv[]) {
	if (argc < 3) {
		perror ("File not specified!\n");
		exit (1);
	}

	FILE *fpi = fopen (argv[1], "rb+");

	if (fpi == NULL) {
		perror ("Can't open input file!\n");
		exit (1);
	}

	FILE *fpo = fopen (argv[2], "wb+");

	if (fpo == NULL) {
		perror ("Can't open output file!\n");
		exit (1);
	}

	fseek (fpi, 1, SEEK_END);
	long f_sz = ftell (fpi);									// File SiZe
	printf ("Source File Size: %ld bytes.\n", f_sz);
	rewind (fpi);

	parse (fpi, fpo, f_sz);

	fclose (fpo);
	fclose (fpi);

	return 0;
}