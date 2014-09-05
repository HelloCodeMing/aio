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

/*
 * 读文件
 * param：cb，回调函数
 */
int aio_read(int fd, void *buff, size_t len, void(*cb)(read_arg_t *));

/*
 * 初始化
 */

int aio_init();

/*
 * 销毁
 */
int aio_destroy();
