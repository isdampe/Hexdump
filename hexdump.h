#ifndef HEXDUMP_HEXDUMP_H
#define HEXDUMP_HEXDUMP_H
#include <stdio.h>

struct hexdump_session {
	char input_file[4096];
	unsigned int bytes_per_line;
};

enum hexdump_status {
	HEXDUMP_STATUS_OK,
	HEXDUMP_STATUS_ERR_FOPEN
};

enum hexdump_status hexdump_process(struct hexdump_session *session);
static inline void hexdump_print(uint8_t *buffer, const int min_line_size, const int buffer_length);
static inline char hexdump_ascii(const char c);

#endif
