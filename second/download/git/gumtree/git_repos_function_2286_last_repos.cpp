static int create_tmpfile(struct strbuf *tmp, const char *filename)
{
	int fd, dirlen = directory_size(filename);

	strbuf_reset(tmp);
	strbuf_add(tmp, filename, dirlen);
	strbuf_addstr(tmp, "tmp_obj_XXXXXX");
	fd = git_mkstemp_mode(tmp->buf, 0444);
	if (fd < 0 && dirlen && errno == ENOENT) {
		/*
		 * Make sure the directory exists; note that the contents
		 * of the buffer are undefined after mkstemp returns an
		 * error, so we have to rewrite the whole buffer from
		 * scratch.
		 */
		strbuf_reset(tmp);
		strbuf_add(tmp, filename, dirlen - 1);
		if (mkdir(tmp->buf, 0777) && errno != EEXIST)
			return -1;
		if (adjust_shared_perm(tmp->buf))
			return -1;

		/* Try again */
		strbuf_addstr(tmp, "/tmp_obj_XXXXXX");
		fd = git_mkstemp_mode(tmp->buf, 0444);
	}
	return fd;
}