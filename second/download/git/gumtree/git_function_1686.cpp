void prune_shallow(int show_only)
{
	static struct lock_file shallow_lock;
	struct strbuf sb = STRBUF_INIT;
	int fd;

	if (show_only) {
		write_shallow_commits_1(&sb, 0, NULL, SEEN_ONLY | VERBOSE);
		strbuf_release(&sb);
		return;
	}
	fd = hold_lock_file_for_update(&shallow_lock, git_path("shallow"),
				       LOCK_DIE_ON_ERROR);
	check_shallow_file_for_update();
	if (write_shallow_commits_1(&sb, 0, NULL, SEEN_ONLY)) {
		if (write_in_full(fd, sb.buf, sb.len) != sb.len)
			die_errno("failed to write to %s",
				  shallow_lock.filename);
		commit_lock_file(&shallow_lock);
	} else {
		unlink(git_path("shallow"));
		rollback_lock_file(&shallow_lock);
	}
	strbuf_release(&sb);
}