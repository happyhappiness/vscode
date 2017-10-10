					 writeout_error);
			if (ret)
				return ret;
		}
	}

	if (!active_cache_tree)
		active_cache_tree = cache_tree();

	if (!cache_tree_fully_valid(active_cache_tree))
		cache_tree_update(&the_index, WRITE_TREE_SILENT | WRITE_TREE_REPAIR);

	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
		die(_("unable to write new index file"));

	if (!opts->force && !opts->quiet)
		show_local_changes(&new->commit->object, &opts->diff_options);

