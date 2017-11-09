static int handle_boundary(struct mailinfo *mi, struct strbuf *line)
{
	struct strbuf newline = STRBUF_INIT;

	strbuf_addch(&newline, '\n');
again:
	if (line->len >= (*(mi->content_top))->len + 2 &&
	    !memcmp(line->buf + (*(mi->content_top))->len, "--", 2)) {
		/* we hit an end boundary */
		/* pop the current boundary off the stack */
		strbuf_release(*(mi->content_top));
		FREE_AND_NULL(*(mi->content_top));

		/* technically won't happen as is_multipart_boundary()
		   will fail first.  But just in case..
		 */
		if (--mi->content_top < mi->content) {
			error("Detected mismatched boundaries, can't recover");
			mi->input_error = -1;
			mi->content_top = mi->content;
			return 0;
		}
		handle_filter(mi, &newline);
		strbuf_release(&newline);
		if (mi->input_error)
			return 0;

		/* skip to the next boundary */
		if (!find_boundary(mi, line))
			return 0;
		goto again;
	}

	/* set some defaults */
	mi->transfer_encoding = TE_DONTCARE;
	strbuf_reset(&mi->charset);

	/* slurp in this section's info */
	while (read_one_header_line(line, mi->input))
		check_header(mi, line, mi->p_hdr_data, 0);

	strbuf_release(&newline);
	/* replenish line */
	if (strbuf_getline_lf(line, mi->input))
		return 0;
	strbuf_addch(line, '\n');
	return 1;
}