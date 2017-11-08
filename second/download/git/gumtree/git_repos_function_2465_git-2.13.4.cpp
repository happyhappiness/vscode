static int check_header(struct mailinfo *mi,
			const struct strbuf *line,
			struct strbuf *hdr_data[], int overwrite)
{
	int i, ret = 0, len;
	struct strbuf sb = STRBUF_INIT;

	/* search for the interesting parts */
	for (i = 0; header[i]; i++) {
		int len = strlen(header[i]);
		if ((!hdr_data[i] || overwrite) && cmp_header(line, header[i])) {
			/* Unwrap inline B and Q encoding, and optionally
			 * normalize the meta information to utf8.
			 */
			strbuf_add(&sb, line->buf + len + 2, line->len - len - 2);
			decode_header(mi, &sb);
			handle_header(&hdr_data[i], &sb);
			ret = 1;
			goto check_header_out;
		}
	}

	/* Content stuff */
	if (cmp_header(line, "Content-Type")) {
		len = strlen("Content-Type: ");
		strbuf_add(&sb, line->buf + len, line->len - len);
		decode_header(mi, &sb);
		strbuf_insert(&sb, 0, "Content-Type: ", len);
		handle_content_type(mi, &sb);
		ret = 1;
		goto check_header_out;
	}
	if (cmp_header(line, "Content-Transfer-Encoding")) {
		len = strlen("Content-Transfer-Encoding: ");
		strbuf_add(&sb, line->buf + len, line->len - len);
		decode_header(mi, &sb);
		handle_content_transfer_encoding(mi, &sb);
		ret = 1;
		goto check_header_out;
	}
	if (cmp_header(line, "Message-Id")) {
		len = strlen("Message-Id: ");
		strbuf_add(&sb, line->buf + len, line->len - len);
		decode_header(mi, &sb);
		if (mi->add_message_id)
			mi->message_id = strbuf_detach(&sb, NULL);
		ret = 1;
		goto check_header_out;
	}

check_header_out:
	strbuf_release(&sb);
	return ret;
}