	bol += strlen(needle);
	eol = strchrnul(bol, '\n');
	*eol = '\0';
	return bol;
}

static void handle_commit(struct commit *commit, struct rev_info *rev)
{
	int saved_output_format = rev->diffopt.output_format;
	const char *commit_buffer;
	const char *author, *author_end, *committer, *committer_end;
	const char *encoding, *message;
	char *reencoded = NULL;
	struct commit_list *p;
	int i;

	rev->diffopt.output_format = DIFF_FORMAT_CALLBACK;

	parse_commit_or_die(commit);
	commit_buffer = get_commit_buffer(commit, NULL);
