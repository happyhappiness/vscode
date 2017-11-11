void rerere_gc(struct string_list *rr)
{
	struct string_list to_remove = STRING_LIST_INIT_DUP;
	DIR *dir;
	struct dirent *e;
	int i;
	time_t now = time(NULL);
	int cutoff_noresolve = 15;
	int cutoff_resolve = 60;

	if (setup_rerere(rr, 0) < 0)
		return;

	git_config_get_int("gc.rerereresolved", &cutoff_resolve);
	git_config_get_int("gc.rerereunresolved", &cutoff_noresolve);
	git_config(git_default_config, NULL);
	dir = opendir(git_path("rr-cache"));
	if (!dir)
		die_errno("unable to open rr-cache directory");
	/* Collect stale conflict IDs ... */
	while ((e = readdir(dir))) {
		struct rerere_dir *rr_dir;
		struct rerere_id id;
		int now_empty;

		if (is_dot_or_dotdot(e->d_name))
			continue;
		rr_dir = find_rerere_dir(e->d_name);
		if (!rr_dir)
			continue; /* or should we remove e->d_name? */

		now_empty = 1;
		for (id.variant = 0, id.collection = rr_dir;
		     id.variant < id.collection->status_nr;
		     id.variant++) {
			prune_one(&id, now, cutoff_resolve, cutoff_noresolve);
			if (id.collection->status[id.variant])
				now_empty = 0;
		}
		if (now_empty)
			string_list_append(&to_remove, e->d_name);
	}
	closedir(dir);

	/* ... and then remove the empty directories */
	for (i = 0; i < to_remove.nr; i++)
		rmdir(git_path("rr-cache/%s", to_remove.items[i].string));
	string_list_clear(&to_remove, 0);
	rollback_lock_file(&write_lock);
}