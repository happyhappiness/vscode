static void handle_body(void)
{
	struct strbuf prev = STRBUF_INIT;

	/* Skip up to the first boundary */
	if (*content_top) {
		if (!find_boundary())
			goto handle_body_out;
	}

	do {
		/* process any boundary lines */
		if (*content_top && is_multipart_boundary(&line)) {
			/* flush any leftover */
			if (prev.len) {
				handle_filter(&prev);
				strbuf_reset(&prev);
			}
			if (!handle_boundary())
				goto handle_body_out;
		}

		/* Unwrap transfer encoding */
		decode_transfer_encoding(&line);

		switch (transfer_encoding) {
		case TE_BASE64:
		case TE_QP:
		{
			struct strbuf **lines, **it, *sb;

			/* Prepend any previous partial lines */
			strbuf_insert(&line, 0, prev.buf, prev.len);
			strbuf_reset(&prev);

			/*
			 * This is a decoded line that may contain
			 * multiple new lines.  Pass only one chunk
			 * at a time to handle_filter()
			 */
			lines = strbuf_split(&line, '\n');
			for (it = lines; (sb = *it); it++) {
				if (*(it + 1) == NULL) /* The last line */
					if (sb->buf[sb->len - 1] != '\n') {
						/* Partial line, save it for later. */
						strbuf_addbuf(&prev, sb);
						break;
					}
				handle_filter(sb);
			}
			/*
			 * The partial chunk is saved in "prev" and will be
			 * appended by the next iteration of read_line_with_nul().
			 */
			strbuf_list_free(lines);
			break;
		}
		default:
			handle_filter(&line);
		}

	} while (!strbuf_getwholeline(&line, fin, '\n'));

handle_body_out:
	strbuf_release(&prev);
}