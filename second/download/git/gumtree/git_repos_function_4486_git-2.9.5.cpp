int cmd_config(int argc, const char **argv, const char *prefix)
{
	int nongit = !startup_info->have_repository;
	char *value;

	given_config_source.file = getenv(CONFIG_ENVIRONMENT);

	argc = parse_options(argc, argv, prefix, builtin_config_options,
			     builtin_config_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	if (use_global_config + use_system_config + use_local_config +
	    !!given_config_source.file + !!given_config_source.blob > 1) {
		error("only one config file at a time.");
		usage_with_options(builtin_config_usage, builtin_config_options);
	}

	if (given_config_source.file &&
			!strcmp(given_config_source.file, "-")) {
		given_config_source.file = NULL;
		given_config_source.use_stdin = 1;
	}

	if (use_global_config) {
		char *user_config = expand_user_path("~/.gitconfig");
		char *xdg_config = xdg_config_home("config");

		if (!user_config)
			/*
			 * It is unknown if HOME/.gitconfig exists, so
			 * we do not know if we should write to XDG
			 * location; error out even if XDG_CONFIG_HOME
			 * is set and points at a sane location.
			 */
			die("$HOME not set");

		if (access_or_warn(user_config, R_OK, 0) &&
		    xdg_config && !access_or_warn(xdg_config, R_OK, 0))
			given_config_source.file = xdg_config;
		else
			given_config_source.file = user_config;
	}
	else if (use_system_config)
		given_config_source.file = git_etc_gitconfig();
	else if (use_local_config)
		given_config_source.file = git_pathdup("config");
	else if (given_config_source.file) {
		if (!is_absolute_path(given_config_source.file) && prefix)
			given_config_source.file =
				xstrdup(prefix_filename(prefix,
							strlen(prefix),
							given_config_source.file));
	}

	if (respect_includes == -1)
		respect_includes = !given_config_source.file;

	if (end_null) {
		term = '\0';
		delim = '\n';
		key_delim = '\n';
	}

	if (HAS_MULTI_BITS(types)) {
		error("only one type at a time.");
		usage_with_options(builtin_config_usage, builtin_config_options);
	}

	if ((actions & (ACTION_GET_COLOR|ACTION_GET_COLORBOOL)) && types) {
		error("--get-color and variable type are incoherent");
		usage_with_options(builtin_config_usage, builtin_config_options);
	}

	if (HAS_MULTI_BITS(actions)) {
		error("only one action at a time.");
		usage_with_options(builtin_config_usage, builtin_config_options);
	}
	if (actions == 0)
		switch (argc) {
		case 1: actions = ACTION_GET; break;
		case 2: actions = ACTION_SET; break;
		case 3: actions = ACTION_SET_ALL; break;
		default:
			usage_with_options(builtin_config_usage, builtin_config_options);
		}
	if (omit_values &&
	    !(actions == ACTION_LIST || actions == ACTION_GET_REGEXP)) {
		error("--name-only is only applicable to --list or --get-regexp");
		usage_with_options(builtin_config_usage, builtin_config_options);
	}

	if (show_origin && !(actions &
		(ACTION_GET|ACTION_GET_ALL|ACTION_GET_REGEXP|ACTION_LIST))) {
		error("--show-origin is only applicable to --get, --get-all, "
			  "--get-regexp, and --list.");
		usage_with_options(builtin_config_usage, builtin_config_options);
	}

	if (actions == ACTION_LIST) {
		check_argc(argc, 0, 0);
		if (git_config_with_options(show_all_config, NULL,
					    &given_config_source,
					    respect_includes) < 0) {
			if (given_config_source.file)
				die_errno("unable to read config file '%s'",
					  given_config_source.file);
			else
				die("error processing config file(s)");
		}
	}
	else if (actions == ACTION_EDIT) {
		char *config_file;

		check_argc(argc, 0, 0);
		if (!given_config_source.file && nongit)
			die("not in a git directory");
		if (given_config_source.use_stdin)
			die("editing stdin is not supported");
		if (given_config_source.blob)
			die("editing blobs is not supported");
		git_config(git_default_config, NULL);
		config_file = xstrdup(given_config_source.file ?
				      given_config_source.file : git_path("config"));
		if (use_global_config) {
			int fd = open(config_file, O_CREAT | O_EXCL | O_WRONLY, 0666);
			if (fd) {
				char *content = default_user_config();
				write_str_in_full(fd, content);
				free(content);
				close(fd);
			}
			el