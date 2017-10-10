static int save_todo(struct todo_list *todo_list, struct replay_opts *opts)
{
	static struct lock_file todo_lock;
	const char *todo_path = get_todo_path(opts);
	int next = todo_list->current, offset, fd;

	fd = hold_lock_file_for_update(&todo_lock, todo_path, 0);
	if (fd < 0)
		return error_errno(_("could not lock '%s'"), todo_path);
	offset = next < todo_list->nr ?
		todo_list->items[next].offset_in_buf : todo_list->buf.len;
	if (write_in_full(fd, todo_list->buf.buf + offset,
			todo_list->buf.len - offset) < 0)
		return error_errno(_("could not write to '%s'"), todo_path);
	if (commit_lock_file(&todo_lock) < 0)
		return error(_("failed to finalize '%s'."), todo_path);
	return 0;
}

static int save_opts(struct replay_opts *opts)
{
	const char *opts_file = git_path_opts_file();
