	int i;

	git_setup_gettext();

	git_extract_argv0_path(argv[0]);
	set_die_routine(die_webcgi);

	if (!method)
		die("No REQUEST_METHOD from server");
	if (!strcmp(method, "HEAD"))
		method = "GET";
	dir = getdir();
