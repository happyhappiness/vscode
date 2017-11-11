void append_signoff(struct strbuf *msgbuf, int ignore_footer, unsigned flag)
{
	unsigned no_dup_sob = flag & APPEND_SIGNOFF_DEDUP;
	struct strbuf sob = STRBUF_INIT;
	int has_footer;

	strbuf_addstr(&sob, sign_off_header);
	strbuf_addstr(&sob, fmt_name(getenv("GIT_COMMITTER_NAME"),
				getenv("GIT_COMMITTER_EMAIL")));
	strbuf_addch(&sob, '\n');

	/*
	 * If the whole message buffer is equal to the sob, pretend that we
	 * found a conforming footer with a matching sob
	 */
	if (msgbuf->len - ignore_footer == sob.len &&
	    !strncmp(msgbuf->buf, sob.buf, sob.len))
		has_footer = 3;
	else
		has_footer = has_conforming_footer(msgbuf, &sob, ignore_footer);

	if (!has_footer) {
		const char *append_newlines = NULL;
		size_t len = msgbuf->len - ignore_footer;

		if (!len) {
			/*
			 * The buffer is completely empty.  Leave foom for
			 * the title and body to be filled in by the user.
			 */
			append_newlines = "\n\n";
		} else if (msgbuf->buf[len - 1] != '\n') {
			/*
			 * Incomplete line.  Complete the line and add a
			 * blank one so that there is an empty line between
			 * the message body and the sob.
			 */
			append_newlines = "\n\n";
		} else if (len == 1) {
			/*
			 * Buffer contains a single newline.  Add another
			 * so that we leave room for the title and body.
			 */
			append_newlines = "\n";
		} else if (msgbuf->buf[len - 2] != '\n') {
			/*
			 * Buffer ends with a single newline.  Add another
			 * so that there is an empty line between the message
			 * body and the sob.
			 */
			append_newlines = "\n";
		} /* else, the buffer already ends with two newlines. */

		if (append_newlines)
			strbuf_splice(msgbuf, msgbuf->len - ignore_footer, 0,
				append_newlines, strlen(append_newlines));
	}

	if (has_footer != 3 && (!no_dup_sob || has_footer != 2))
		strbuf_splice(msgbuf, msgbuf->len - ignore_footer, 0,
				sob.buf, sob.len);

	strbuf_release(&sob);
}