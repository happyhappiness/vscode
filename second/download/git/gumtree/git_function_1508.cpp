static int guess_repository_type(const char *git_dir)
{
	char cwd[PATH_MAX];
	const char *slash;

	/*
	 * "GIT_DIR=. git init" is always bare.
	 * "GIT_DIR=`pwd` git init" too.
	 */
	if (!strcmp(".", git_dir))
		return 1;
	if (!getcwd(cwd, sizeof(cwd)))
		die_errno(_("cannot tell cwd"));
	if (!strcmp(git_dir, cwd))
		return 1;
	/*
	 * "GIT_DIR=.git or GIT_DIR=something/.git is usually not.
	 */
	if (!strcmp(git_dir, ".git"))
		return 0;
	slash = strrchr(git_dir, '/');
	if (slash && !strcmp(slash, "/.git"))
		return 0;

	/*
	 * Otherwise it is often bare.  At this point
	 * we are just guessing.
	 */
	return 1;
}