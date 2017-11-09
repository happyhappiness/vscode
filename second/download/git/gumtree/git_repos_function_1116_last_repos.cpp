static int read_rebase_todolist(const char *fname, struct string_list *lines)
{
	struct strbuf line = STRBUF_INIT;
	FILE *f = fopen(git_path("%s", fname), "r");

	if (!f) {
		if (errno == ENOENT)
			return -1;
		die_errno("Could not open file %s for reading",
			  git_path("%s", fname));
	}
	while (!strbuf_getline_lf(&line, f)) {
		if (line.len && line.buf[0] == comment_line_char)
			continue;
		strbuf_trim(&line);
		if (!line.len)
			continue;
		abbrev_sha1_in_line(&line);
		string_list_append(lines, line.buf);
	}
	fclose(f);
	return 0;
}