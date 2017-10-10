	git_config(git_default_config, NULL);
	dir = opendir(git_path("rr-cache"));
	if (!dir)
		die_errno("unable to open rr-cache directory");
	/* Collect stale conflict IDs ... */
	while ((e = readdir(dir))) {
		if (is_dot_or_dotdot(e->d_name))
			continue;

		then = rerere_last_used_at(e->d_name);
		if (then) {
			cutoff = cutoff_resolve;
		} else {
			then = rerere_created_at(e->d_name);
			if (!then)
				continue;
			cutoff = cutoff_noresolve;
		}
		if (then < now - cutoff * 86400)
			string_list_append(&to_remove, e->d_name);
	}
	closedir(dir);
	/* ... and then remove them one-by-one */
	for (i = 0; i < to_remove.nr; i++)
		unlink_rr_item(dirname_to_id(to_remove.items[i].string));
	string_list_clear(&to_remove, 0);
	rollback_lock_file(&write_lock);
}

/*
 * During a conflict resolution, after "rerere" recorded the
