static void add_path(struct strbuf *out, const char *path)
{
	if (path && *path) {
		if (is_absolute_path(path))
			strbuf_addstr(out, path);
		else
			strbuf_addstr(out, absolute_path(path));

		strbuf_addch(out, PATH_SEP);
	}
}