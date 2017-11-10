const char *get_git_namespace(void)
{
	if (!namespace)
		setup_git_env();
	return namespace;
}