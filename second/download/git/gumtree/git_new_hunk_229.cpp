	struct strbuf buf = STRBUF_INIT;
	int nongit;

	git_extract_argv0_path(argv[0]);
	setup_git_directory_gently(&nongit);
	if (argc < 2) {
		error("remote-curl: usage: git remote-curl <remote> [<url>]");
		return 1;
	}

	options.verbosity = 1;
	options.progress = !!isatty(2);
	options.thin = 1;
