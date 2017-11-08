static int hash_literally(unsigned char *sha1, int fd, const char *type, unsigned flags)
{
	struct strbuf buf = STRBUF_INIT;
	int ret;

	if (strbuf_read(&buf, fd, 4096) < 0)
		ret = -1;
	else if (flags & HASH_WRITE_OBJECT)
		ret = write_sha1_file(buf.buf, buf.len, type, sha1);
	else
		ret = hash_sha1_file(buf.buf, buf.len, type, sha1);
	strbuf_release(&buf);
	return ret;
}