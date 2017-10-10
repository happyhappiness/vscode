		die("BUG: your snprintf is broken");
	if (len >= max)
		die("BUG: attempt to snprintf into too-small buffer");
	return len;
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

int write_file(const char *path, const char *fmt, ...)
{
	int status;
	va_list params;

	va_start(params, fmt);
	status = write_file_v(path, 1, fmt, params);
	va_end(params);
	return status;
}

int write_file_gently(const char *path, const char *fmt, ...)
{
	int status;
	va_list params;

	va_start(params, fmt);
	status = write_file_v(path, 0, fmt, params);
	va_end(params);
	return status;
}

void sleep_millisec(int millisec)
{
	poll(NULL, 0, millisec);
}
