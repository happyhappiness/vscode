	safe_create_leading_directories_const(name);
	return open(name, O_RDWR|O_CREAT|O_EXCL, 0600);
}

char *get_index_file(void)
{
	if (!git_index_file)
		setup_git_env();
	return git_index_file;
}

char *get_graft_file(void)
{
	if (!git_graft_file)
		setup_git_env();
	return git_graft_file;
}

int set_git_dir(const char *path)
{
	if (setenv(GIT_DIR_ENVIRONMENT, path, 1))
		return error("Could not set GIT_DIR to '%s'", path);
	setup_git_env();
	return 0;
}

const char *get_log_output_encoding(void)
{
