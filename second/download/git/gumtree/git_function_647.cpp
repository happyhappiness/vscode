static void save_todo(struct commit_list *todo_list, struct replay_opts *opts)
{
	static struct lock_file todo_lock;
	struct strbuf buf = STRBUF_INIT;
	int fd;

	fd = hold_lock_file_for_update(&todo_lock, git_path_todo_file(), LOCK_DIE_ON_ERROR);
	if (format_todo(&buf, todo_list, opts) < 0)
		die(_("Could not format %s."), git_path_todo_file());
	if (write_in_full(fd, buf.buf, buf.len) < 0) {
		strbuf_release(&buf);
		die_errno(_("Could not write to %s"), git_path_todo_file());
	}
	if (commit_lock_file(&todo_lock) < 0) {
		strbuf_release(&buf);
		die(_("Error wrapping up %s."), git_path_todo_file());
	}
	strbuf_release(&buf);
}