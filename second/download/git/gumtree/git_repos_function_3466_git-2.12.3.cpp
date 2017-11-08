int is_submodule_populated(const char *path)
{
	int ret = 0;
	char *gitdir = xstrfmt("%s/.git", path);

	if (resolve_gitdir(gitdir))
		ret = 1;

	free(gitdir);
	return ret;
}