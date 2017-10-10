	if (!strcmp(k, "pack.threads")) {
		delta_search_threads = git_config_int(k, v);
		if (delta_search_threads < 0)
			die("invalid number of threads specified (%d)",
			    delta_search_threads);
#ifdef NO_PTHREADS
		if (delta_search_threads != 1)
			warning("no threads support, ignoring %s", k);
#endif
		return 0;
	}
	if (!strcmp(k, "pack.indexversion")) {
		pack_idx_opts.version = git_config_int(k, v);
		if (pack_idx_opts.version > 2)
