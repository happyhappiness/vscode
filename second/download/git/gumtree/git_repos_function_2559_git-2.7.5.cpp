static int show_http_message(struct strbuf *type, struct strbuf *charset,
			     struct strbuf *msg)
{
	const char *p, *eol;

	/*
	 * We only show text/plain parts, as other types are likely
	 * to be ugly to look at on the user's terminal.
	 */
	if (strcmp(type->buf, "text/plain"))
		return -1;
	if (charset->len)
		strbuf_reencode(msg, charset->buf, get_log_output_encoding());

	strbuf_trim(msg);
	if (!msg->len)
		return -1;

	p = msg->buf;
	do {
		eol = strchrnul(p, '\n');
		fprintf(stderr, "remote: %.*s\n", (int)(eol - p), p);
		p = eol + 1;
	} while(*eol);
	return 0;
}