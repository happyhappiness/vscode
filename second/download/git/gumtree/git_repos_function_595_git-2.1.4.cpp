static void record_author_date(struct author_date_slab *author_date,
			       struct commit *commit)
{
	const char *buf, *line_end, *ident_line;
	const char *buffer = get_commit_buffer(commit, NULL);
	struct ident_split ident;
	char *date_end;
	unsigned long date;

	for (buf = buffer; buf; buf = line_end + 1) {
		line_end = strchrnul(buf, '\n');
		if (!skip_prefix(buf, "author ", &ident_line)) {
			if (!line_end[0] || line_end[1] == '\n')
				return; /* end of header */
			continue;
		}
		if (split_ident_line(&ident,
				     ident_line, line_end - ident_line) ||
		    !ident.date_begin || !ident.date_end)
			goto fail_exit; /* malformed "author" line */
		break;
	}

	date = strtoul(ident.date_begin, &date_end, 10);
	if (date_end != ident.date_end)
		goto fail_exit; /* malformed date */
	*(author_date_slab_at(author_date, commit)) = date;

fail_exit:
	unuse_commit_buffer(commit, buffer);
}