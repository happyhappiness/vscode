const char *get_git_namespace(void)
{
	if (!namespace)
		BUG("git environment hasn't been setup");
	return namespace;
}