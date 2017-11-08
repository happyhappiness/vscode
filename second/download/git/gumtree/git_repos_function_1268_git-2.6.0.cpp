static void do_submodule_path(struct strbuf *buf, const char *path,
			      const char *fmt, va_list args)
{
	const char *git_dir;

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

	strbuf_vaddf(buf, fmt, args);
	strbuf_cleanup_path(buf);
}