const char *setup_git_directory(void)
{
	return setup_git_directory_gently(NULL);
}