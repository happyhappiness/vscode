const char *git_path_submodule(const char *path, const char *fmt, ...)
{
	struct strbuf *buf = get_pathname();
	const char *git_dir;
	va_list args;

	strbuf_addstr(buf, path);
	if (buf->len && buf->buf[buf->len - 1] != '/')
		strbuf_addch(buf, '/');
	strbuf_addstr(buf, ".git");

	git_dir = read_gitfile(buf->buf);
	if (git_dir) {
		strbuf_reset(buf);
		strbuf_addstr(buf, git_dir);
	}
	strbuf_addch(buf, '/');

	va_start(args, fmt);
	strbuf_vaddf(buf, fmt, args);
	va_end(args);
	strbuf_cleanup_path(buf);
	return buf->buf;
}