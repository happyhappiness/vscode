static void emit_hunk_header(struct emit_callback *ecbdata,
			     const char *line, int len)
{
	const char *context = diff_get_color(ecbdata->color_diff, DIFF_CONTEXT);
	const char *frag = diff_get_color(ecbdata->color_diff, DIFF_FRAGINFO);
	const char *func = diff_get_color(ecbdata->color_diff, DIFF_FUNCINFO);
	const char *reset = diff_get_color(ecbdata->color_diff, DIFF_RESET);
	static const char atat[2] = { '@', '@' };
	const char *cp, *ep;
	struct strbuf msgbuf = STRBUF_INIT;
	int org_len = len;
	int i = 1;

	/*
	 * As a hunk header must begin with "@@ -<old>, +<new> @@",
	 * it always is at least 10 bytes long.
	 */
	if (len < 10 ||
	    memcmp(line, atat, 2) ||
	    !(ep = memmem(line + 2, len - 2, atat, 2))) {
		emit_line(ecbdata->opt, context, reset, line, len);
		return;
	}
	ep += 2; /* skip over @@ */

	/* The hunk header in fraginfo color */
	strbuf_addstr(&msgbuf, frag);
	strbuf_add(&msgbuf, line, ep - line);
	strbuf_addstr(&msgbuf, reset);

	/*
	 * trailing "\r\n"
	 */
	for ( ; i < 3; i++)
		if (line[len - i] == '\r' || line[len - i] == '\n')
			len--;

	/* blank before the func header */
	for (cp = ep; ep - line < len; ep++)
		if (*ep != ' ' && *ep != '\t')
			break;
	if (ep != cp) {
		strbuf_addstr(&msgbuf, context);
		strbuf_add(&msgbuf, cp, ep - cp);
		strbuf_addstr(&msgbuf, reset);
	}

	if (ep < line + len) {
		strbuf_addstr(&msgbuf, func);
		strbuf_add(&msgbuf, ep, line + len - ep);
		strbuf_addstr(&msgbuf, reset);
	}

	strbuf_add(&msgbuf, line + len, org_len - len);
	emit_line(ecbdata->opt, "", "", msgbuf.buf, msgbuf.len);
	strbuf_release(&msgbuf);
}