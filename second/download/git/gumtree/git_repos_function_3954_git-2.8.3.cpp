static const char *quote_crnl(const char *path)
{
	static struct strbuf new_path = STRBUF_INIT;

	if (!path)
		return NULL;

	strbuf_reset(&new_path);

	while (*path) {
		switch (*path) {
		case '\\': strbuf_addstr(&new_path, "\\\\"); break;
		case '\n': strbuf_addstr(&new_path, "\\n"); break;
		case '\r': strbuf_addstr(&new_path, "\\r"); break;
		default:
			strbuf_addch(&new_path, *path);
		}
		path++;
	}
	return new_path.buf;
}