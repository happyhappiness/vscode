	flush_output(o);
	for (i = o->call_depth; i--;)
		fputs("  ", stdout);
	if (commit->util)
		printf("virtual %s\n", merge_remote_util(commit)->name);
	else {
		printf("%s ", find_unique_abbrev(commit->object.sha1, DEFAULT_ABBREV));
		if (parse_commit(commit) != 0)
			printf(_("(bad commit)\n"));
		else {
			const char *title;
			const char *msg = get_commit_buffer(commit, NULL);
			int len = find_commit_subject(msg, &title);
