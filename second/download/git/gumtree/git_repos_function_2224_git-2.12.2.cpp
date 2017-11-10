static void add_path(struct strbuf *out, const char *path)
{
	if (path && *path) {
		strbuf_add_absolute_path(out, path);
		strbuf_addch(out, PATH_SEP);
	}
}