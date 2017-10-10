		if (!strcmp(argv[i], "--")) {
			has_dashdash = 1;
			break;
		}
	}

	prefix = setup_git_directory();
	git_config(git_default_config, NULL);
	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];

		if (!strcmp(arg, "--git-path")) {
			if (!argv[i + 1])
				die("--git-path requires an argument");
			puts(git_path("%s", argv[i + 1]));
			i++;
			continue;
