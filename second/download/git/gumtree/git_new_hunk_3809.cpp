	for (xopt = opts->xopts; xopt != opts->xopts + opts->xopts_nr; xopt++)
		parse_merge_opt(&o, *xopt);

	clean = merge_trees(&o,
			    head_tree,
			    next_tree, base_tree, &result);
	strbuf_release(&o.obuf);
	if (clean < 0)
		return clean;

	if (active_cache_changed &&
	    write_locked_index(&the_index, &index_lock, COMMIT_LOCK))
		/* TRANSLATORS: %s will be "revert" or "cherry-pick" */
		die(_("%s: Unable to write new index file"), action_name(opts));
	rollback_lock_file(&index_lock);
