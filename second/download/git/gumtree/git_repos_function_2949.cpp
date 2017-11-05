void rerere_gc(struct string_list *rr)
{
	struct string_list to_remove = STRING_LIST_INIT_DUP;
	DIR *dir;
	struct dirent *e;
	int i, cutoff;
	time_t now = time(NULL), then;
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
	for (i = 0; i < to_remove.nr; i++)
		unlink_rr_item(to_remove.items[i].string);
	string_list_clear(&to_remove, 0);
	rollback_lock_file(&write_lock);
}