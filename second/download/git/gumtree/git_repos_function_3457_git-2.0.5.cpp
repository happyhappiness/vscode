void trace_argv_printf(const char **argv, const char *fmt, ...)
{
	struct strbuf buf = STRBUF_INIT;
	va_list ap;
	int fd, need_close = 0;

	fd = get_trace_fd("GIT_TRACE", &need_close);
	if (!fd)
		return;

	set_try_to_free_routine(NULL);	/* is never reset */
	va_start(ap, fmt);
	strbuf_vaddf(&buf, fmt, ap);
	va_end(ap);

	sq_quote_argv(&buf, argv, 0);
	strbuf_addch(&buf, '\n');
	write_or_whine_pipe(fd, buf.buf, buf.len, err_msg);
	strbuf_release(&buf);

	if (need_close)
		close(fd);
}