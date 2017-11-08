static int index_stream_convert_blob(unsigned char *sha1, int fd,
				     const char *path, unsigned flags)
{
	int ret;
	const int write_object = flags & HASH_WRITE_OBJECT;
	struct strbuf sbuf = STRBUF_INIT;

	assert(path);
	assert(would_convert_to_git_filter_fd(path));

	convert_to_git_filter_fd(path, fd, &sbuf,
				 write_object ? safe_crlf : SAFE_CRLF_FALSE);

	if (write_object)
		ret = write_sha1_file(sbuf.buf, sbuf.len, typename(OBJ_BLOB),
				      sha1);
	else
		ret = hash_sha1_file(sbuf.buf, sbuf.len, typename(OBJ_BLOB),
				     sha1);
	strbuf_release(&sbuf);
	return ret;
}