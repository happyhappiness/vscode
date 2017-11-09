static int read_oneliner(struct strbuf *buf,
	const char *path, int skip_if_empty)
{
	int orig_len = buf->len;

	if (!file_exists(path))
		return 0;

	if (strbuf_read_file(buf, path, 0) < 0) {
		warning_errno(_("could not read '%s'"), path);
		return 0;
	}

	if (buf->len > orig_len && buf->buf[buf->len - 1] == '\n') {
		if (--buf->len > orig_len && buf->buf[buf->len - 1] == '\r')
			--buf->len;
		buf->buf[buf->len] = '\0';
	}

	if (skip_if_empty && buf->len == orig_len)
		return 0;

	return 1;
}