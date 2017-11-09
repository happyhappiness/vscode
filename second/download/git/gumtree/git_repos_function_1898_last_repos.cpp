int have_git_dir(void)
{
	return startup_info->have_repository
		|| the_repository->gitdir;
}