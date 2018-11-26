#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "hexdump.h"

enum hexdump_status hexdump_process(const struct hexdump_session *session)
{
	FILE *fd = NULL;
	size_t file_size = 0;
	size_t bytes_read = 0;
	uint8_t buffer[session->bytes_per_line];

	fd = fopen(session->input_file, "r");
	if (fd == NULL)
		return HEXDUMP_STATUS_ERR_FOPEN;

	fseek(fd, 0, SEEK_END);
	file_size = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	while (bytes_read < file_size) {
		size_t r = fread(buffer, sizeof(uint8_t), session->bytes_per_line, fd);
		hexdump_print(buffer, session->bytes_per_line, r, bytes_read);
		bytes_read += r;
	}

	fclose(fd);

	return HEXDUMP_STATUS_OK;
}

static inline void hexdump_print(const uint8_t *buffer, const int min_line_size, const int buffer_length,
		const size_t offset)
{
	//Hex dump.
	printf("%06x    ", offset);
	for (int i=0; i<min_line_size; ++i) {
		if (i < buffer_length)
			printf("%02x ", buffer[i]);
		else
			printf("   ");
	}
	printf("    ");

	//Ascii table.
	for (int i=0; i<min_line_size; ++i) {
		if (i < buffer_length)
			printf("%c", hexdump_ascii(buffer[i]));
		else
			printf(" ");
	}
	printf("\n");
}

static inline char hexdump_ascii(const char c)
{
	return (c >= 33 && c < 127) ? c : '.';
}
