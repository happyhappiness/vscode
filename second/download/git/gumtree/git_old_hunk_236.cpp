
	clean = merge_trees(&o,
			    head_tree,
			    next_tree, base_tree, &result);

	if (active_cache_changed &&
	    (write_cache(index_fd, active_cache, active_nr) ||
	     commit_locked_index(&index_lock)))
		/* TRANSLATORS: %s will be "revert" or "cherry-pick" */
		die(_("%s: Unable to write new index file"), action_name(opts));
	rollback_lock_file(&index_lock);

	if (opts->signoff)
		append_signoff(msgbuf, 0, 0);
