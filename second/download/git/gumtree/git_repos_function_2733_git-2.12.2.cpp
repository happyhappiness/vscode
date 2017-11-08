static const char *get_todo_path(const struct replay_opts *opts)
{
	if (is_rebase_i(opts))
		return rebase_path_todo();
	return git_path_todo_file();
}