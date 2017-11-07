static int show_http_message(struct strbuf *type, struct strbuf *msg)
{
	const char *p, *eol;

	/*
	 * We only show text/plain parts, as other types are likely
	 * to be ugly to look at on the user's terminal.
	 *
	 * TODO should handle "; charset=XXX", and re-encode into
	 * logoutputencoding
	 */
	if (strcasecmp(type->buf, "text/plain"))
		return -1;

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