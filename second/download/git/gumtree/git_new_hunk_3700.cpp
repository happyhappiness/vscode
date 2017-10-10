	DIR *dir = opendir(git_path("worktrees"));
	struct dirent *d;
	int ret;
	if (!dir)
		return;
	while ((d = readdir(dir)) != NULL) {
		if (is_dot_or_dotdot(d->d_name))
			continue;
		strbuf_reset(&reason);
		if (!prune_worktree(d->d_name, &reason))
			continue;
		if (show_only || verbose)
			printf("%s\n", reason.buf);
