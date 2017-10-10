	strbuf_release(&o.obuf);
	if (clean < 0)
		return clean;

	if (active_cache_changed &&
	    write_locked_index(&the_index, &index_lock, COMMIT_LOCK))
		/* TRANSLATORS: %s will be "revert", "cherry-pick" or
		 * "rebase -i".
		 */
		return error(_("%s: Unable to write new index file"),
			_(action_name(opts)));
	rollback_lock_file(&index_lock);

