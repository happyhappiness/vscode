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