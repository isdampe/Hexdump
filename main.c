#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "hexdump.h"

static void usage()
{
	printf("Usage: hexdump -i [input_file] [opts]\n");
	printf("Options:\n");
	printf("\t-i  The input file to dump.\n");
	printf("\t-n  Number of bytes to render per line.\n");
}

int main(int argc, char **argv)
{
	struct hexdump_session session;
	session.input_file[0] = '\0';
	session.bytes_per_line = 8;

	int opt;
	while ((opt = getopt(argc, argv, "i:n:h:")) != -1) {
		switch (opt) {
			case 'i':
				strcpy(session.input_file, optarg);
				break;
			case 'n':
				session.bytes_per_line = atoi(optarg);
				break;
		}
	}

	if (strlen(session.input_file) < 1) {
		usage();
		return 1;
	}

	if (hexdump_process(&session) != HEXDUMP_STATUS_OK)
		return 1;

	return 0;
}