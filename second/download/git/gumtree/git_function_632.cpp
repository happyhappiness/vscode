static int read_and_refresh_cache(struct replay_opts *opts)
{
	static struct lock_file index_lock;
	int index_fd = hold_locked_index(&index_lock, 0);
	if (read_index_preload(&the_index, NULL) < 0) {
		rollback_lock_file(&index_lock);
		return error(_("git %s: failed to read the index"),
			_(action_name(opts)));
	}
	refresh_index(&the_index, REFRESH_QUIET|REFRESH_UNMERGED, NULL, NULL, NULL);
	if (the_index.cache_changed && index_fd >= 0) {
		if (write_locked_index(&the_index, &index_lock, COMMIT_LOCK)) {
			rollback_lock_file(&index_lock);
			return error(_("git %s: failed to refresh the index"),
				_(action_name(opts)));
		}
	}
	rollback_lock_file(&index_lock);
	return 0;
}