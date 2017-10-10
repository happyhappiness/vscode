					 writeout_error);
			if (ret)
				return ret;
		}
	}

	if (write_cache(newfd, active_cache, active_nr) ||
	    commit_locked_index(lock_file))
		die(_("unable to write new index file"));

	if (!opts->force && !opts->quiet)
		show_local_changes(&new->commit->object, &opts->diff_options);

	return 0;
