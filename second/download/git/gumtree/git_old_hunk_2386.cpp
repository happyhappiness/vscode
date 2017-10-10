		      enum object_type type, const char *path,
		      unsigned flags)
{
	int ret;

	if (!size) {
		ret = index_mem(sha1, NULL, size, type, path, flags);
	} else if (size <= SMALL_FILE_SIZE) {
		char *buf = xmalloc(size);
		if (size == read_in_full(fd, buf, size))
			ret = index_mem(sha1, buf, size, type, path, flags);
		else
			ret = error("short read %s", strerror(errno));
