void check_repository_format(void)
{
	check_repository_format_gently(get_git_dir(), NULL);
	startup_info->have_repository = 1;
}