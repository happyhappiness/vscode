static int write_helper(void *fd, const void *buf, size_t len)
{
	return write((intptr_t)fd, buf, len);
}