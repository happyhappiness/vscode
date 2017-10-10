}

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

	if (!strcmp(strategy, "recursive") || !strcmp(strategy, "subtree")) {
		int clean, x;
		struct commit *result;
		struct commit_list *reversed = NULL;
		struct merge_options o;
		struct commit_list *j;

		if (remoteheads->next) {
			error(_("Not handling anything other than two heads merge."));
