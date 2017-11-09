static void strip_last_component(struct strbuf *path)
{
	size_t offset = offset_1st_component(path->buf);
	size_t len = path->len;

	/* Find start of the last component */
	while (offset < len && !is_dir_sep(path->buf[len - 1]))
		len--;
	/* Skip sequences of multiple path-separators */
	while (offset < len && is_dir_sep(path->buf[len - 1]))
		len--;

	strbuf_setlen(path, len);
}