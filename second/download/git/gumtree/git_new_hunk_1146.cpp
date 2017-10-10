
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
