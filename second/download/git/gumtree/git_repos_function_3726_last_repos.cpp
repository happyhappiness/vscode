int is_submodule_populated_gently(const char *path, int *return_error_code)
{
	int ret = 0;
	char *gitdir = xstrfmt("%s/.git", path);

	if (resolve_gitdir_gently(gitdir, return_error_code))
		ret = 1;

	free(gitdir);
	return ret;
}