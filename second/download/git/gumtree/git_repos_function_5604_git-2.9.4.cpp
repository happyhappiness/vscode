static int hash_literally(unsigned char *sha1, int fd, const char *type, unsigned flags)
{
	struct strbuf buf = STRBUF_INIT;
	int ret;

	if (strbuf_read(&buf, fd, 4096) < 0)
		ret = -1;
	else
		ret = hash_sha1_file_literally(buf.buf, buf.len, type, sha1, flags);
	strbuf_release(&buf);
	return ret;
}