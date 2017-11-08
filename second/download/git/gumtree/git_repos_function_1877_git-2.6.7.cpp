int check_repository_format(void)
{
	return check_repository_format_gently(get_git_dir(), NULL);
}