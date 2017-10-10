	return 0;
}

static int write_buffer(int fd, const void *buf, size_t len)
{
	if (write_in_full(fd, buf, len) < 0)
		return error("file write error (%s)", strerror(errno));
	return 0;
}

int hash_sha1_file(const void *buf, unsigned long len, const char *type,
                   unsigned char *sha1)
{
