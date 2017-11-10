struct sha1file *sha1fd_throughput(int fd, const char *name, struct progress *tp)
{
	struct sha1file *f = xmalloc(sizeof(*f));
	f->fd = fd;
	f->check_fd = -1;
	f->offset = 0;
	f->total = 0;
	f->tp = tp;
	f->name = name;
	f->do_crc = 0;
	git_SHA1_Init(&f->ctx);
	return f;
}