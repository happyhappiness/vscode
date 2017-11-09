static int repo_init_gitdir(struct repository *repo, const char *gitdir)
{
	int ret = 0;
	int error = 0;
	char *abspath = NULL;
	const char *resolved_gitdir;

	abspath = real_pathdup(gitdir, 0);
	if (!abspath) {
		ret = -1;
		goto out;
	}

	/* 'gitdir' must reference the gitdir directly */
	resolved_gitdir = resolve_gitdir_gently(abspath, &error);
	if (!resolved_gitdir) {
		ret = -1;
		goto out;
	}

	repo_set_gitdir(repo, resolved_gitdir);

out:
	free(abspath);
	return ret;
}