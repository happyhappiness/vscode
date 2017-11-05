static void do_submodule_path(struct strbuf *buf, const char *path,
			      const char *fmt, va_list args)
{
	const char *git_dir;
	struct strbuf git_submodule_common_dir = STRBUF_INIT;
	struct strbuf git_submodule_dir = STRBUF_INIT;

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
	strbuf_addstr(&git_submodule_dir, buf->buf);

	strbuf_vaddf(buf, fmt, args);

	if (get_common_dir_noenv(&git_submodule_common_dir, git_submodule_dir.buf))
		update_common_dir(buf, git_submodule_dir.len, git_submodule_common_dir.buf);

	strbuf_cleanup_path(buf);

	strbuf_release(&git_submodule_dir);
	strbuf_release(&git_submodule_common_dir);
}