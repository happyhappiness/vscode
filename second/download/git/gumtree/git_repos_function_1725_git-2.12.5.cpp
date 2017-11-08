int have_git_dir(void)
{
	return startup_info->have_repository
		|| git_dir
		|| getenv(GIT_DIR_ENVIRONMENT);
}