		set_git_work_tree(".");

	/* set_git_work_tree() must have been called by now */
	worktree = get_git_work_tree();

	/* both get_git_work_tree() and cwd are already normalized */
	if (!strcmp(cwd, worktree)) { /* cwd == worktree */
		set_git_dir(gitdirenv);
		free(gitfile);
		return NULL;
	}

	offset = dir_inside_of(cwd, worktree);
	if (offset >= 0) {	/* cwd inside worktree? */
		set_git_dir(real_path(gitdirenv));
		if (chdir(worktree))
			die_errno("Could not chdir to '%s'", worktree);
		cwd[len++] = '/';
		cwd[len] = '\0';
		free(gitfile);
		return cwd + offset;
	}

	/* cwd outside worktree */
	set_git_dir(gitdirenv);
	free(gitfile);
	return NULL;
}

static const char *setup_discovered_git_dir(const char *gitdir,
					    char *cwd, int offset, int len,
					    int *nongit_ok)
{
	if (check_repository_format_gently(gitdir, nongit_ok))
		return NULL;

	/* --work-tree is set without --git-dir; use discovered one */
	if (getenv(GIT_WORK_TREE_ENVIRONMENT) || git_work_tree_cfg) {
		if (offset != len && !is_absolute_path(gitdir))
			gitdir = xstrdup(real_path(gitdir));
		if (chdir(cwd))
			die_errno("Could not come back to cwd");
		return setup_explicit_git_dir(gitdir, cwd, len, nongit_ok);
	}

	/* #16.2, #17.2, #20.2, #21.2, #24, #25, #28, #29 (see t1510) */
	if (is_bare_repository_cfg > 0) {
		set_git_dir(offset == len ? gitdir : real_path(gitdir));
		if (chdir(cwd))
			die_errno("Could not come back to cwd");
		return NULL;
	}

	/* #0, #1, #5, #8, #9, #12, #13 */
	set_git_work_tree(".");
	if (strcmp(gitdir, DEFAULT_GIT_DIR_ENVIRONMENT))
		set_git_dir(gitdir);
	inside_git_dir = 0;
	inside_work_tree = 1;
	if (offset == len)
		return NULL;

	/* Make "offset" point to past the '/', and add a '/' at the end */
	offset++;
	cwd[len++] = '/';
	cwd[len] = 0;
	return cwd + offset;
}

/* #16.1, #17.1, #20.1, #21.1, #22.1 (see t1510) */
static const char *setup_bare_git_dir(char *cwd, int offset, int len, int *nongit_ok)
{
	int root_len;

	if (check_repository_format_gently(".", nongit_ok))
		return NULL;

	setenv(GIT_IMPLICIT_WORK_TREE_ENVIRONMENT, "0", 1);

	/* --work-tree is set without --git-dir; use discovered one */
	if (getenv(GIT_WORK_TREE_ENVIRONMENT) || git_work_tree_cfg) {
		const char *gitdir;

		gitdir = offset == len ? "." : xmemdupz(cwd, offset);
		if (chdir(cwd))
			die_errno("Could not come back to cwd");
		return setup_explicit_git_dir(gitdir, cwd, len, nongit_ok);
	}

	inside_git_dir = 1;
	inside_work_tree = 0;
	if (offset != len) {
		if (chdir(cwd))
			die_errno("Cannot come back to cwd");
		root_len = offset_1st_component(cwd);
		cwd[offset > root_len ? offset : root_len] = '\0';
		set_git_dir(cwd);
	}
	else
		set_git_dir(".");
	return NULL;
}

