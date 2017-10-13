static const char *setup_explicit_git_dir(const char *gitdirenv,
					  struct strbuf *cwd,
					  int *nongit_ok)
{
	const char *work_tree_env = getenv(GIT_WORK_TREE_ENVIRONMENT);
	const char *worktree;
	char *gitfile;
	int offset;

	if (PATH_MAX - 40 < strlen(gitdirenv))
		die("'$%s' too big", GIT_DIR_ENVIRONMENT);

	gitfile = (char*)read_gitfile(gitdirenv);
	if (gitfile) {
		gitfile = xstrdup(gitfile);
		gitdirenv = gitfile;
	}

	if (!is_git_directory(gitdirenv)) {
		if (nongit_ok) {
			*nongit_ok = 1;
			free(gitfile);
			return NULL;
		}
		die("Not a git repository: '%s'", gitdirenv);
	}

	if (check_repository_format_gently(gitdirenv, nongit_ok)) {
		free(gitfile);
		return NULL;
	}

	/* #3, #7, #11, #15, #19, #23, #27, #31 (see t1510) */
	if (work_tree_env)
		set_git_work_tree(work_tree_env);
	else if (is_bare_repository_cfg > 0) {
		if (git_work_tree_cfg) /* #22.2, #30 */
			die("core.bare and core.worktree do not make sense");

		/* #18, #26 */
		set_git_dir(gitdirenv);
		free(gitfile);
		return NULL;
	}
	else if (git_work_tree_cfg) { /* #6, #14 */
		if (is_absolute_path(git_work_tree_cfg))
			set_git_work_tree(git_work_tree_cfg);
		else {
			char *core_worktree;
			if (chdir(gitdirenv))
				die_errno("Could not chdir to '%s'", gitdirenv);
			if (chdir(git_work_tree_cfg))
				die_errno("Could not chdir to '%s'", git_work_tree_cfg);
			core_worktree = xgetcwd();
			if (chdir(cwd->buf))
				die_errno("Could not come back to cwd");
			set_git_work_tree(core_worktree);
			free(core_worktree);
		}
	}
	else if (!git_env_bool(GIT_IMPLICIT_WORK_TREE_ENVIRONMENT, 1)) {
		/* #16d */
		set_git_dir(gitdirenv);
		free(gitfile);
		return NULL;
	}
	else /* #2, #10 */
		set_git_work_tree(".");

	/* set_git_work_tree() must have been called by now */
	worktree = get_git_work_tree();

	/* both get_git_work_tree() and cwd are already normalized */
	if (!strcmp(cwd->buf, worktree)) { /* cwd == worktree */
		set_git_dir(gitdirenv);
		free(gitfile);
		return NULL;
	}

	offset = dir_inside_of(cwd->buf, worktree);
	if (offset >= 0) {	/* cwd inside worktree? */
		set_git_dir(real_path(gitdirenv));
		if (chdir(worktree))
			die_errno("Could not chdir to '%s'", worktree);
		strbuf_addch(cwd, '/');
		free(gitfile);
		return cwd->buf + offset;
	}

	/* cwd outside worktree */
	set_git_dir(gitdirenv);
	free(gitfile);
	return NULL;
}