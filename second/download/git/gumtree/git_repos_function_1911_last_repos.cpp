int set_git_dir(const char *path)
{
	if (setenv(GIT_DIR_ENVIRONMENT, path, 1))
		return error("Could not set GIT_DIR to '%s'", path);
	repo_set_gitdir(the_repository, path);
	setup_git_env();
	return 0;
}