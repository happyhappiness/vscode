static void handle_body(struct mailinfo *mi, struct strbuf *line)
{
	struct strbuf prev = STRBUF_INIT;

	/* Skip up to the first boundary */
	if (*(mi->content_top)) {
		if (!find_boundary(mi, line))
			goto handle_body_out;
	}

	do {
		/* process any boundary lines */
		if (*(mi->content_top) && is_multipart_boundary(mi, line)) {
			/* flush any leftover */
			if (prev.len) {
				handle_filter(mi, &prev);
				strbuf_reset(&prev);
			}
			if (!handle_boundary(mi, line))
				goto handle_body_out;
		}

		/* Unwrap transfer encoding */
		decode_transfer_encoding(mi, line);

		switch (mi->transfer_encoding) {
		case TE_BASE64:
		case TE_QP:
		{
			struct strbuf **lines, **it, *sb;

			/* Prepend any previous partial lines */
			strbuf_insert(line, 0, prev.buf, prev.len);
			strbuf_reset(&prev);

			/*
			 * This is a decoded line that may contain
			 * multiple new lines.  Pass only one chunk
			 * at a time to handle_filter()
			 */
			lines = strbuf_split(line, '\n');
			for (it = lines; (sb = *it); it++) {
				if (*(it + 1) == NULL) /* The last line */
					if (sb->buf[sb->len - 1] != '\n') {
						/* Partial line, save it for later. */
						strbuf_addbuf(&prev, sb);
						break;
					}
				handle_filter(mi, sb);
			}
			/*
			 * The partial chunk is saved in "prev" and will be
			 * appended by the next iteration of read_line_with_nul().
			 */
			strbuf_list_free(lines);
			break;
		}
		default:
			handle_filter(mi, line);
		}

		if (mi->input_error)
			break;
	} while (!strbuf_getwholeline(line, mi->input, '\n'));

	flush_inbody_header_accum(mi);

handle_body_out:
	strbuf_release(&prev);
}