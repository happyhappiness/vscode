	struct strbuf sb = STRBUF_INIT;
	if (strbuf_getcwd(&sb))
		die_errno(_("unable to get current working directory"));
	return strbuf_detach(&sb, NULL);
}

static int write_file_v(const char *path, int fatal,
			const char *fmt, va_list params)
{
	struct strbuf sb = STRBUF_INIT;
	int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0) {
		if (fatal)
			die_errno(_("could not open %s for writing"), path);
		return -1;
	}
	strbuf_vaddf(&sb, fmt, params);
	strbuf_complete_line(&sb);
	if (write_in_full(fd, sb.buf, sb.len) != sb.len) {
		int err = errno;
		close(fd);
		strbuf_release(&sb);
		errno = err;
		if (fatal)
