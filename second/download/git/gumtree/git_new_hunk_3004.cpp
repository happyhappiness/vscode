	git_config_get_int("gc.rerereresolved", &cutoff_resolve);
	git_config_get_int("gc.rerereunresolved", &cutoff_noresolve);
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
