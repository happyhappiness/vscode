	struct strbuf line = STRBUF_INIT;
	FILE *f = fopen(git_path("%s", fname), "r");

	if (!f)
		die_errno("Could not open file %s for reading",
			  git_path("%s", fname));
	while (!strbuf_getline_lf(&line, f)) {
		if (line.len && line.buf[0] == comment_line_char)
			continue;
		strbuf_trim(&line);
		if (!line.len)
			continue;
		abbrev_sha1_in_line(&line);
