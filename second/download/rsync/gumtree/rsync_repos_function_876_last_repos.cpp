int sys_lsetxattr(const char *path, const char *name, const void *value, size_t size)
{
	int attrfd;
	size_t bufpos;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

	if ((attrfd = attropen(path, name, O_CREAT|O_TRUNC|O_WRONLY, mode)) < 0)
		return -1;

	for (bufpos = 0; bufpos < size; ) {
		ssize_t cnt = write(attrfd, value+bufpos, size);
		if (cnt <= 0) {
			if (cnt < 0 && errno == EINTR)
				continue;
			bufpos = -1;
			break;
		}
		bufpos += cnt;
	}

	close(attrfd);

	return bufpos > 0 ? 0 : -1;
}