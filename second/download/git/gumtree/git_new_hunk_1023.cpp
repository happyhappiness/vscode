	struct dirent *e;
	struct strbuf path = STRBUF_INIT;
	const char *buffer = get_commit_buffer(partial_commit, NULL);
	const char *msg = strstr(buffer, "\n\n");
	int baselen;

	git_path_buf(&path, NOTES_MERGE_WORKTREE);
	if (o->verbosity >= 3)
		printf("Committing notes in notes merge worktree at %s\n",
			path.buf);

	if (!msg || msg[2] == '\0')
		die("partial notes commit has empty message");
