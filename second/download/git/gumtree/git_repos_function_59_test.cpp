int remove_signature(struct strbuf *buf)
{
	const char *line = buf->buf;
	const char *tail = buf->buf + buf->len;
	int in_signature = 0;
	const char *sig_start = NULL;
	const char *sig_end = NULL;

	while (line < tail) {
		const char *next = memchr(line, '\n', tail - line);
		next = next ? next + 1 : tail;

		if (in_signature && line[0] == ' ')
			sig_end = next;
		else if (starts_with(line, gpg_sig_header) &&
			 line[gpg_sig_header_len] == ' ') {
			sig_start = line;
			sig_end = next;
			in_signature = 1;
		} else {
			if (*line == '\n')
				/* dump the whole remainder of the buffer */
				next = tail;
			in_signature = 0;
		}
		line = next;
	}

	if (sig_start)
		strbuf_remove(buf, sig_start - buf->buf, sig_end - sig_start);

	return sig_start != NULL;
}