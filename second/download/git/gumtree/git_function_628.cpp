static int parse_insn_buffer(char *buf, struct commit_list **todo_list,
			struct replay_opts *opts)
{
	struct commit_list **next = todo_list;
	struct commit *commit;
	char *p = buf;
	int i;

	for (i = 1; *p; i++) {
		char *eol = strchrnul(p, '\n');
		commit = parse_insn_line(p, eol, opts);
		if (!commit)
			return error(_("Could not parse line %d."), i);
		next = commit_list_append(commit, next);
		p = *eol ? eol + 1 : eol;
	}
	if (!*todo_list)
		return error(_("No commits parsed."));
	return 0;
}