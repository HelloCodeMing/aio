#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

#include "aio.h"

void read_cb(read_arg_t *arg) {
	write(1, arg->buff, arg->len);
	free(arg);
}

int main(int arvc, char **argv)
{
	int fd;
	char buffer[64];
	const char *file_name = "/tmp/test";

	if ((fd = open(file_name, O_RDONLY)) == -1) {
		perror("open failed");
		exit(1);
	}
	if (aio_init() != 0) {
		perror("aio_init failed");
		exit(1);
	}
	aio_read(fd, buffer, 64, read_cb);
	aio_destroy();
	return 0;
}
