static int sha1write_ewah_helper(void *f, const void *buf, size_t len)
{
	/* sha1write will die on error */
	sha1write(f, buf, len);
	return len;
}