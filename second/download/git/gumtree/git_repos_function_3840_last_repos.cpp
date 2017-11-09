static void append_basename(struct strbuf *path, const char *dir, const char *file)
{
	const char *tail = strrchr(file, '/');

	strbuf_addstr(path, dir);
	while (path->len && path->buf[path->len - 1] == '/')
		path->len--;
	strbuf_addch(path, '/');
	strbuf_addstr(path, tail ? tail + 1 : file);
}