static void record_author_date(struct author_date_slab *author_date,
			       struct commit *commit)
{
	const char *buffer = get_commit_buffer(commit, NULL);
	struct ident_split ident;
	const char *ident_line;
	size_t ident_len;
	char *date_end;
	unsigned long date;

	ident_line = find_commit_header(buffer, "author", &ident_len);
	if (!ident_line)
		goto fail_exit; /* no author line */
	if (split_ident_line(&ident, ident_line, ident_len) ||
	    !ident.date_begin || !ident.date_end)
		goto fail_exit; /* malformed "author" line */

	date = strtoul(ident.date_begin, &date_end, 10);
	if (date_end != ident.date_end)
		goto fail_exit; /* malformed date */
	*(author_date_slab_at(author_date, commit)) = date;

fail_exit:
	unuse_commit_buffer(commit, buffer);
}