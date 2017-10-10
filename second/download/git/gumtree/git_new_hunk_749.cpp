static int save_todo(struct todo_list *todo_list, struct replay_opts *opts)
{
	static struct lock_file todo_lock;
	const char *todo_path = get_todo_path(opts);
	int next = todo_list->current, offset, fd;

	/*
	 * rebase -i writes "git-rebase-todo" without the currently executing
	 * command, appending it to "done" instead.
	 */
	if (is_rebase_i(opts))
		next++;

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

	if (is_rebase_i(opts)) {
		const char *done_path = rebase_path_done();
		int fd = open(done_path, O_CREAT | O_WRONLY | O_APPEND, 0666);
		int prev_offset = !next ? 0 :
			todo_list->items[next - 1].offset_in_buf;

		if (fd >= 0 && offset > prev_offset &&
		    write_in_full(fd, todo_list->buf.buf + prev_offset,
				  offset - prev_offset) < 0) {
			close(fd);
			return error_errno(_("could not write to '%s'"),
					   done_path);
		}
		if (fd >= 0)
			close(fd);
	}
	return 0;
}

static int save_opts(struct replay_opts *opts)
{
	const char *opts_file = git_path_opts_file();
