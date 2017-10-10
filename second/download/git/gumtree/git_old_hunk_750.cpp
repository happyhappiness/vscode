							"options.strategy-option",
							opts->xopts[i], "^$", 0);
	}
	return res;
}

static int pick_commits(struct todo_list *todo_list, struct replay_opts *opts)
{
	int res;

	setenv(GIT_REFLOG_ACTION, action_name(opts), 0);
	if (opts->allow_ff)
		assert(!(opts->signoff || opts->no_commit ||
				opts->record_origin || opts->edit));
	if (read_and_refresh_cache(opts))
		return -1;

	while (todo_list->current < todo_list->nr) {
		struct todo_item *item = todo_list->items + todo_list->current;
		if (save_todo(todo_list, opts))
			return -1;
		res = do_pick_commit(item->command, item->commit, opts);
		todo_list->current++;
		if (res)
			return res;
	}

	/*
	 * Sequence of picks finished successfully; cleanup by
	 * removing the .git/sequencer directory
	 */
	return sequencer_remove_state(opts);
}
