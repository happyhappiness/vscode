static int pick_commits(struct commit_list *todo_list, struct replay_opts *opts)
{
	struct commit_list *cur;
	int res;

	setenv(GIT_REFLOG_ACTION, action_name(opts), 0);
	if (opts->allow_ff)
		assert(!(opts->signoff || opts->no_commit ||
				opts->record_origin || opts->edit));
	read_and_refresh_cache(opts);

	for (cur = todo_list; cur; cur = cur->next) {
		save_todo(cur, opts);
		res = do_pick_commit(cur->item, opts);
		if (res)
			return res;
	}

	/*
	 * Sequence of picks finished successfully; cleanup by
	 * removing the .git/sequencer directory
	 */
	remove_sequencer_state();
	return 0;
}