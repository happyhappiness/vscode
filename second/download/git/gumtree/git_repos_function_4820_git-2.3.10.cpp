static int handle_boundary(void)
{
	struct strbuf newline = STRBUF_INIT;

	strbuf_addch(&newline, '\n');
again:
	if (line.len >= (*content_top)->len + 2 &&
	    !memcmp(line.buf + (*content_top)->len, "--", 2)) {
		/* we hit an end boundary */
		/* pop the current boundary off the stack */
		strbuf_release(*content_top);
		free(*content_top);
		*content_top = NULL;

		/* technically won't happen as is_multipart_boundary()
		   will fail first.  But just in case..
		 */
		if (--content_top < content) {
			fprintf(stderr, "Detected mismatched boundaries, "
					"can't recover\n");
			exit(1);
		}
		handle_filter(&newline);
		strbuf_release(&newline);

		/* skip to the next boundary */
		if (!find_boundary())
			return 0;
		goto again;
	}

	/* set some defaults */
	transfer_encoding = TE_DONTCARE;
	strbuf_reset(&charset);

	/* slurp in this section's info */
	while (read_one_header_line(&line, fin))
		check_header(&line, p_hdr_data, 0);

	strbuf_release(&newline);
	/* replenish line */
	if (strbuf_getline(&line, fin, '\n'))
		return 0;
	strbuf_addch(&line, '\n');
	return 1;
}