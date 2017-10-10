	struct dirent *e;
	int i, cutoff;
	time_t now = time(NULL), then;
	int cutoff_noresolve = 15;
	int cutoff_resolve = 60;

	git_config_get_int("gc.rerereresolved", &cutoff_resolve);
	git_config_get_int("gc.rerereunresolved", &cutoff_noresolve);
	git_config(git_default_config, NULL);
	dir = opendir(git_path("rr-cache"));
	if (!dir)
		die_errno("unable to open rr-cache directory");
