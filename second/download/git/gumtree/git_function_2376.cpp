static int handle_commit_msg(struct strbuf *line)
{
	static int still_looking = 1;

	if (!cmitmsg)
		return 0;

	if (still_looking) {
		if (!line->len || (line->len == 1 && line->buf[0] == '\n'))
			return 0;
	}

	if (use_inbody_headers && still_looking) {
		still_looking = check_header(line, s_hdr_data, 0);
		if (still_looking)
			return 0;
	} else
		/* Only trim the first (blank) line of the commit message
		 * when ignoring in-body headers.
		 */
		still_looking = 0;

	/* normalize the log message to UTF-8. */
	if (metainfo_charset)
		convert_to_utf8(line, charset.buf);

	if (use_scissors && is_scissors_line(line)) {
		int i;
		if (fseek(cmitmsg, 0L, SEEK_SET))
			die_errno("Could not rewind output message file");
		if (ftruncate(fileno(cmitmsg), 0))
			die_errno("Could not truncate output message file at scissors");
		still_looking = 1;

		/*
		 * We may have already read "secondary headers"; purge
		 * them to give ourselves a clean restart.
		 */
		for (i = 0; header[i]; i++) {
			if (s_hdr_data[i])
				strbuf_release(s_hdr_data[i]);
			s_hdr_data[i] = NULL;
		}
		return 0;
	}

	if (patchbreak(line)) {
		if (message_id)
			fprintf(cmitmsg, "Message-Id: %s\n", message_id);
		fclose(cmitmsg);
		cmitmsg = NULL;
		return 1;
	}

	fputs(line->buf, cmitmsg);
	return 0;
}