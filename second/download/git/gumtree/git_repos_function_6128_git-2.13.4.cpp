static int try_merge_strategy(const char *strategy, struct commit_list *common,
			      struct commit_list *remoteheads,
			      struct commit *head)
{
	static struct lock_file lock;
	const char *head_arg = "HEAD";

	hold_locked_index(&lock, LOCK_DIE_ON_ERROR);
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
			return 2;
		}

		init_merge_options(&o);
		if (!strcmp(strategy, "subtree"))
			o.subtree_shift = "";

		o.renormalize = option_renormalize;
		o.show_rename_progress =
			show_progress == -1 ? isatty(2) : show_progress;

		for (x = 0; x < xopts_nr; x++)
			if (parse_merge_opt(&o, xopts[x]))
				die(_("Unknown option for merge-recursive: -X%s"), xopts[x]);

		o.branch1 = head_arg;
		o.branch2 = merge_remote_util(remoteheads->item)->name;

		for (j = common; j; j = j->next)
			commit_list_insert(j->item, &reversed);

		hold_locked_index(&lock, LOCK_DIE_ON_ERROR);
		clean = merge_recursive(&o, head,
				remoteheads->item, reversed, &result);
		if (clean < 0)
			exit(128);
		if (active_cache_changed &&
		    write_locked_index(&the_index, &lock, COMMIT_LOCK))
			die (_("unable to write %s"), get_index_file());
		rollback_lock_file(&lock);
		return clean ? 0 : 1;
	} else {
		return try_merge_command(strategy, xopts_nr, xopts,
						common, head_arg, remoteheads);
	}
}