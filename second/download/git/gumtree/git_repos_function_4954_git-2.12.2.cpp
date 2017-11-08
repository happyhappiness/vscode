static void read_from_stdin(struct shortlog *log)
{
	struct strbuf author = STRBUF_INIT;
	struct strbuf oneline = STRBUF_INIT;
	static const char *author_match[2] = { "Author: ", "author " };
	static const char *committer_match[2] = { "Commit: ", "committer " };
	const char **match;

	match = log->committer ? committer_match : author_match;
	while (strbuf_getline_lf(&author, stdin) != EOF) {
		const char *v;
		if (!skip_prefix(author.buf, match[0], &v) &&
		    !skip_prefix(author.buf, match[1], &v))
			continue;
		while (strbuf_getline_lf(&oneline, stdin) != EOF &&
		       oneline.len)
			; /* discard headers */
		while (strbuf_getline_lf(&oneline, stdin) != EOF &&
		       !oneline.len)
			; /* discard blanks */
		insert_one_record(log, v, oneline.buf);
	}
	strbuf_release(&author);
	strbuf_release(&oneline);
}