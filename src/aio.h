#ifndef TPOOL_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#endif

typedef struct read_arg_s {
	int fd;
	void *buff;
	size_t len;
	void (*cb)(struct read_arg_s *);
}read_arg_t;

int aio_read(int fd, void *buff, size_t len, void(*cb)(read_arg_t *));

int aio_init();

int aio_destroy();
