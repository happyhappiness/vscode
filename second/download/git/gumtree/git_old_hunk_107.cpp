}

static int try_merge_strategy(const char *strategy, struct commit_list *common,
			      struct commit_list *remoteheads,
			      struct commit *head, const char *head_arg)
{
	int index_fd;
	struct lock_file *lock = xcalloc(1, sizeof(struct lock_file));

	index_fd = hold_locked_index(lock, 1);
	refresh_cache(REFRESH_QUIET);
	if (active_cache_changed &&
			(write_cache(index_fd, active_cache, active_nr) ||
			 commit_locked_index(lock)))
		return error(_("Unable to write index."));
	rollback_lock_file(lock);

	if (!strcmp(strategy, "recursive") || !strcmp(strategy, "subtree")) {
		int clean, x;
		struct commit *result;
		struct lock_file *lock = xcalloc(1, sizeof(struct lock_file));
		int index_fd;
		struct commit_list *reversed = NULL;
		struct merge_options o;
		struct commit_list *j;

		if (remoteheads->next) {
			error(_("Not handling anything other than two heads merge."));
