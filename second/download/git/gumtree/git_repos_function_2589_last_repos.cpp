static int handle_commit_msg(struct mailinfo *mi, struct strbuf *line)
{
	assert(!mi->filter_stage);

	if (mi->header_stage) {
		if (!line->len || (line->len == 1 && line->buf[0] == '\n')) {
			if (mi->inbody_header_accum.len) {
				flush_inbody_header_accum(mi);
				mi->header_stage = 0;
			}
			return 0;
		}
	}

	if (mi->use_inbody_headers && mi->header_stage) {
		mi->header_stage = check_inbody_header(mi, line);
		if (mi->header_stage)
			return 0;
	} else
		/* Only trim the first (blank) line of the commit message
		 * when ignoring in-body headers.
		 */
		mi->header_stage = 0;

	/* normalize the log message to UTF-8. */
	if (convert_to_utf8(mi, line, mi->charset.buf))
		return 0; /* mi->input_error already set */

	if (mi->use_scissors && is_scissors_line(line->buf)) {
		int i;

		strbuf_setlen(&mi->log_message, 0);
		mi->header_stage = 1;

		/*
		 * We may have already read "secondary headers"; purge
		 * them to give ourselves a clean restart.
		 */
		for (i = 0; header[i]; i++) {
			if (mi->s_hdr_data[i])
				strbuf_release(mi->s_hdr_data[i]);
			mi->s_hdr_data[i] = NULL;
		}
		return 0;
	}

	if (patchbreak(line)) {
		if (mi->message_id)
			strbuf_addf(&mi->log_message,
				    "Message-Id: %s\n", mi->message_id);
		return 1;
	}

	strbuf_addbuf(&mi->log_message, line);
	return 0;
}