int mailinfo(struct mailinfo *mi, const char *msg, const char *patch)
{
	FILE *cmitmsg;
	int peek;
	struct strbuf line = STRBUF_INIT;

	cmitmsg = fopen(msg, "w");
	if (!cmitmsg) {
		perror(msg);
		return -1;
	}
	mi->patchfile = fopen(patch, "w");
	if (!mi->patchfile) {
		perror(patch);
		fclose(cmitmsg);
		return -1;
	}

	mi->p_hdr_data = xcalloc(MAX_HDR_PARSED, sizeof(*(mi->p_hdr_data)));
	mi->s_hdr_data = xcalloc(MAX_HDR_PARSED, sizeof(*(mi->s_hdr_data)));

	do {
		peek = fgetc(mi->input);
		if (peek == EOF) {
			fclose(cmitmsg);
			return error("empty patch: '%s'", patch);
		}
	} while (isspace(peek));
	ungetc(peek, mi->input);

	/* process the email header */
	while (read_one_header_line(&line, mi->input))
		check_header(mi, &line, mi->p_hdr_data, 1);

	handle_body(mi, &line);
	fwrite(mi->log_message.buf, 1, mi->log_message.len, cmitmsg);
	fclose(cmitmsg);
	fclose(mi->patchfile);

	handle_info(mi);
	strbuf_release(&line);
	return mi->input_error;
}