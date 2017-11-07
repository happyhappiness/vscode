static void save_todo(struct commit_list *todo_list, struct replay_opts *opts)
{
	const char *todo_file = git_path(SEQ_TODO_FILE);
	static struct lock_file todo_lock;
	struct strbuf buf = STRBUF_INIT;
	int fd;

	fd = hold_lock_file_for_update(&todo_lock, todo_file, LOCK_DIE_ON_ERROR);
	if (format_todo(&buf, todo_list, opts) < 0)
		die(_("Could not format %s."), todo_file);
	if (write_in_full(fd, buf.buf, buf.len) < 0) {
		strbuf_release(&buf);
		die_errno(_("Could not write to %s"), todo_file);
	}
	if (commit_lock_file(&todo_lock) < 0) {
		strbuf_release(&buf);
		die(_("Error wrapping up %s."), todo_file);
	}
	strbuf_release(&buf);
}