const char *get_git_dir(void)
{
	if (!the_repository->gitdir)
		BUG("git environment hasn't been setup");
	return the_repository->gitdir;
}