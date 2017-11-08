static const char *get_todo_path(const struct replay_opts *opts)
{
	return git_path_todo_file();
}