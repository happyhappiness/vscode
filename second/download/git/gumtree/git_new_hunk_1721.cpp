
	return 0;
}

static int guess_repository_type(const char *git_dir)
{
	const char *slash;
	char *cwd;
	int cwd_is_git_dir;

	/*
	 * "GIT_DIR=. git init" is always bare.
	 * "GIT_DIR=`pwd` git init" too.
	 */
	if (!strcmp(".", git_dir))
		return 1;
	cwd = xgetcwd();
	cwd_is_git_dir = !strcmp(git_dir, cwd);
	free(cwd);
	if (cwd_is_git_dir)
		return 1;
	/*
	 * "GIT_DIR=.git or GIT_DIR=something/.git is usually not.
	 */
	if (!strcmp(git_dir, ".git"))
		return 0;
