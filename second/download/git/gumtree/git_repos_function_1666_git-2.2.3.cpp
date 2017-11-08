static int index_pipe(unsigned char *sha1, int fd, enum object_type type,
		      const char *path, unsigned flags)
{
	struct strbuf sbuf = STRBUF_INIT;
	int ret;

	if (strbuf_read(&sbuf, fd, 4096) >= 0)
		ret = index_mem(sha1, sbuf.buf, sbuf.len, type,	path, flags);
	else
		ret = -1;
	strbuf_release(&sbuf);
	return ret;
}