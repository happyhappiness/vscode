static int try_merge_strategy(const char *strategy, struct commit_list *common,
			      struct commit_list *remoteheads,
			      struct commit *head, const char *head_arg)
{
	static struct lock_file lock;

	hold_locked_index(&lock, 1);
	refresh_cache(REFRESH_QUIET);
	if (active_cache_changed &&
	    write_locked_index(&the_index, &lock, COMMIT_LOCK))
		return error(_("Unable to write index."));
	rollback_lock_file(&lock);

