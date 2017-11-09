const char *get_git_common_dir(void)
{
	if (!the_repository->commondir)
		BUG("git environment hasn't been setup");
	return the_repository->commondir;
}