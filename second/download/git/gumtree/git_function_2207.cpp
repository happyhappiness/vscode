static void save_head(const char *head)
{
	const char *head_file = git_path(SEQ_HEAD_FILE);
	static struct lock_file head_lock;
	struct strbuf buf = STRBUF_INIT;
	int fd;

	fd = hold_lock_file_for_update(&head_lock, head_file, LOCK_DIE_ON_ERROR);
	strbuf_addf(&buf, "%s\n", head);
	if (write_in_full(fd, buf.buf, buf.len) < 0)
		die_errno(_("Could not write to %s"), head_file);
	if (commit_lock_file(&head_lock) < 0)
		die(_("Error wrapping up %s."), head_file);
}