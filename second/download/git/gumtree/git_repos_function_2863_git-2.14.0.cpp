int xgethostname(char *buf, size_t len)
{
	/*
	 * If the full hostname doesn't fit in buf, POSIX does not
	 * specify whether the buffer will be null-terminated, so to
	 * be safe, do it ourselves.
	 */
	int ret = gethostname(buf, len);
	if (!ret)
		buf[len - 1] = 0;
	return ret;
}