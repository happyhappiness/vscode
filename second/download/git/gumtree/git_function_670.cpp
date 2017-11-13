static int parse_trailer(struct strbuf *tok, struct strbuf *val, const char *trailer)
{
	size_t len;
	struct strbuf seps = STRBUF_INIT;
	strbuf_addstr(&seps, separators);
	strbuf_addch(&seps, '=');
	len = strcspn(trailer, seps.buf);
	strbuf_release(&seps);
	if (len == 0) {
		int l = strlen(trailer);
		while (l > 0 && isspace(trailer[l - 1]))
			l--;
		return error(_("empty trailer token in trailer '%.*s'"), l, trailer);
	}
	if (len < strlen(trailer)) {
		strbuf_add(tok, trailer, len);
		strbuf_trim(tok);
		strbuf_addstr(val, trailer + len + 1);
		strbuf_trim(val);
	} else {
		strbuf_addstr(tok, trailer);
		strbuf_trim(tok);
	}
	return 0;
}