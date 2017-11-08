static int crlf_to_worktree(const char *path, const char *src, size_t len,
			    struct strbuf *buf, enum crlf_action crlf_action)
{
	char *to_free = NULL;
	struct text_stat stats;

	if (!len || output_eol(crlf_action) != EOL_CRLF)
		return 0;

	gather_stats(src, len, &stats);

	/* No LF? Nothing to convert, regardless. */
	if (!stats.lf)
		return 0;

	/* Was it already in CRLF format? */
	if (stats.lf == stats.crlf)
		return 0;

	if (crlf_action == CRLF_AUTO || crlf_action == CRLF_GUESS) {
		if (crlf_action == CRLF_GUESS) {
			/* If we have any CR or CRLF line endings, we do not touch it */
			/* This is the new safer autocrlf-handling */
			if (stats.cr > 0 || stats.crlf > 0)
				return 0;
		}

		/* If we have any bare CR characters, we're not going to touch it */
		if (stats.cr != stats.crlf)
			return 0;

		if (is_binary(len, &stats))
			return 0;
	}

	/* are we "faking" in place editing ? */
	if (src == buf->buf)
		to_free = strbuf_detach(buf, NULL);

	strbuf_grow(buf, len + stats.lf - stats.crlf);
	for (;;) {
		const char *nl = memchr(src, '\n', len);
		if (!nl)
			break;
		if (nl > src && nl[-1] == '\r') {
			strbuf_add(buf, src, nl + 1 - src);
		} else {
			strbuf_add(buf, src, nl - src);
			strbuf_addstr(buf, "\r\n");
		}
		len -= nl + 1 - src;
		src  = nl + 1;
	}
	strbuf_add(buf, src, len);

	free(to_free);
	return 1;
}