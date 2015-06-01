#include "tpool.h"
#include "aio.h"

static int inited = 0;


static void* aio__read(void *arg) {
	read_arg_t *read_arg = arg;
	while ((read_arg->len = read(read_arg->fd, read_arg->buff, read_arg->len)) != 0) {
		read_arg->cb(read_arg);
	}
}

int aio_read(int fd, void *buff, size_t len, void(*cb)(read_arg_t *arg)) {
	if (!inited)
		aio_init();
	read_arg_t *arg;
	arg = malloc(sizeof(read_arg_t));
	arg->fd = fd;
	arg->buff = buff;
	arg->len = len;
	arg->cb = cb;
	tpool_submit_work(&aio__read, (void*)arg);
}
int  aio_init() {
	if (tpool_create(4) != 0) {
		perror("tpool_create failed");
		return -1;
	}
	inited = 1;
	return 0;
}

int aio_destroy() {
	tpool_destroy();
	inited = 0;
	return 0;
}
