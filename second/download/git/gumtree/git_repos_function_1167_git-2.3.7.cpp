char *git_path_submodule(const char *path, const char *fmt, ...)
{
	char *pathname = get_pathname();
	struct strbuf buf = STRBUF_INIT;
	const char *git_dir;
	va_list args;
	unsigned len;

	len = strlen(path);
	if (len > PATH_MAX-100)
		return bad_path;

	strbuf_addstr(&buf, path);
	if (len && path[len-1] != '/')
		strbuf_addch(&buf, '/');
	strbuf_addstr(&buf, ".git");

	git_dir = read_gitfile(buf.buf);
	if (git_dir) {
		strbuf_reset(&buf);
		strbuf_addstr(&buf, git_dir);
	}
	strbuf_addch(&buf, '/');

	if (buf.len >= PATH_MAX)
		return bad_path;
	memcpy(pathname, buf.buf, buf.len + 1);

	strbuf_release(&buf);
	len = strlen(pathname);

	va_start(args, fmt);
	len += vsnprintf(pathname + len, PATH_MAX - len, fmt, args);
	va_end(args);
	if (len >= PATH_MAX)
		return bad_path;
	return cleanup_path(pathname);
}