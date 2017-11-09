static int save_head(const char *head)
{
	static struct lock_file head_lock;
	struct strbuf buf = STRBUF_INIT;
	int fd;

	fd = hold_lock_file_for_update(&head_lock, git_path_head_file(), 0);
	if (fd < 0) {
		rollback_lock_file(&head_lock);
		return error_errno(_("could not lock HEAD"));
	}
	strbuf_addf(&buf, "%s\n", head);
	if (write_in_full(fd, buf.buf, buf.len) < 0) {
		rollback_lock_file(&head_lock);
		return error_errno(_("could not write to '%s'"),
				   git_path_head_file());
	}
	if (commit_lock_file(&head_lock) < 0) {
		rollback_lock_file(&head_lock);
		return error(_("failed to finalize '%s'."), git_path_head_file());
	}
	return 0;
}