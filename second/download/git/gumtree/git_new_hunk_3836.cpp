		die("BUG: your snprintf is broken");
	if (len >= max)
		die("BUG: attempt to snprintf into too-small buffer");
	return len;
}

void write_file_buf(const char *path, const char *buf, size_t len)
{
	int fd = xopen(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (write_in_full(fd, buf, len) != len)
		die_errno(_("could not write to %s"), path);
	if (close(fd))
		die_errno(_("could not close %s"), path);
}

void write_file(const char *path, const char *fmt, ...)
{
	va_list params;
	struct strbuf sb = STRBUF_INIT;

	va_start(params, fmt);
	strbuf_vaddf(&sb, fmt, params);
	va_end(params);

	strbuf_complete_line(&sb);

	write_file_buf(path, sb.buf, sb.len);
	strbuf_release(&sb);
}

void sleep_millisec(int millisec)
{
	poll(NULL, 0, millisec);
}
