int write_file(const char *path, int fatal, const char *fmt, ...)
{
	struct strbuf sb = STRBUF_INIT;
	va_list params;
	int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0) {
		if (fatal)
			die_errno(_("could not open %s for writing"), path);
		return -1;
	}
	va_start(params, fmt);
	strbuf_vaddf(&sb, fmt, params);
	va_end(params);
	if (write_in_full(fd, sb.buf, sb.len) != sb.len) {
		int err = errno;
		close(fd);
		strbuf_release(&sb);
		errno = err;
		if (fatal)
			die_errno(_("could not write to %s"), path);
		return -1;
	}
	strbuf_release(&sb);
	if (close(fd)) {
		if (fatal)
			die_errno(_("could not close %s"), path);
		return -1;
	}
	return 0;
}