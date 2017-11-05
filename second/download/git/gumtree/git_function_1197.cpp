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
		char *user_config = NULL;
		char *xdg_config = NULL;

		home_config_paths(&user_config, &xdg_config, "config");

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

	if (get_color_slot)
	    actions |= ACTION_GET_COLOR;
	if (get_colorbool_slot)
	    actions |= ACTION_GET_COLORBOOL;

	if ((get_color_slot || get_colorbool_slot) && types) {
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
		const char *config_file = given_config_source.file ?
			given_config_source.file : git_path("config");
		check_argc(argc, 0, 0);
		if (!given_config_source.file && nongit)
			die("not in a git directory");
		if (given_config_source.use_stdin)
			die("editing stdin is not supported");
		if (given_config_source.blob)
			die("editing blobs is not supported");
		git_config(git_default_config, NULL);
		if (use_global_config) {
			int fd = open(config_file, O_CREAT | O_EXCL | O_WRONLY, 0666);
			if (fd) {
				char *content = default_user_config();
				write_str_in_full(fd, content);
				free(content);
				close(fd);
			}
			else if (errno != EEXIST)
				die_errno(_("cannot create configuration file %s"), config_file);
		}
		launch_editor(config_file, NULL, NULL);
	}
	else if (actions == ACTION_SET) {
		int ret;
		check_write();
		check_argc(argc, 2, 2);
		value = normalize_value(argv[0], argv[1]);
		ret = git_config_set_in_file(given_config_source.file, argv[0], value);
		if (ret == CONFIG_NOTHING_SET)
			error("cannot overwrite multiple values with a single value\n"
			"       Use a regexp, --add or --replace-all to change %s.", argv[0]);
		return ret;
	}
	else if (actions == ACTION_SET_ALL) {
		check_write();
		check_argc(argc, 2, 3);
		value = normalize_value(argv[0], argv[1]);
		return git_config_set_multivar_in_file(given_config_source.file,
						       argv[0], value, argv[2], 0);
	}
	else if (actions == ACTION_ADD) {
		check_write();
		check_argc(argc, 2, 2);
		value = normalize_value(argv[0], argv[1]);
		return git_config_set_multivar_in_file(given_config_source.file,
						       argv[0], value,
						       CONFIG_REGEX_NONE, 0);
	}
	else if (actions == ACTION_REPLACE_ALL) {
		check_write();
		check_argc(argc, 2, 3);
		value = normalize_value(argv[0], argv[1]);
		return git_config_set_multivar_in_file(given_config_source.file,
						       argv[0], value, argv[2], 1);
	}
	else if (actions == ACTION_GET) {
		check_argc(argc, 1, 2);
		return get_value(argv[0], argv[1]);
	}
	else if (actions == ACTION_GET_ALL) {
		do_all = 1;
		check_argc(argc, 1, 2);
		return get_value(argv[0], argv[1]);
	}
	else if (actions == ACTION_GET_REGEXP) {
		show_keys = 1;
		use_key_regexp = 1;
		do_all = 1;
		check_argc(argc, 1, 2);
		return get_value(argv[0], argv[1]);
	}
	else if (actions == ACTION_GET_URLMATCH) {
		check_argc(argc, 2, 2);
		return get_urlmatch(argv[0], argv[1]);
	}
	else if (actions == ACTION_UNSET) {
		check_write();
		check_argc(argc, 1, 2);
		if (argc == 2)
			return git_config_set_multivar_in_file(given_config_source.file,
							       argv[0], NULL, argv[1], 0);
		else
			return git_config_set_in_file(given_config_source.file,
						      argv[0], NULL);
	}
	else if (actions == ACTION_UNSET_ALL) {
		check_write();
		check_argc(argc, 1, 2);
		return git_config_set_multivar_in_file(given_config_source.file,
						       argv[0], NULL, argv[1], 1);
	}
	else if (actions == ACTION_RENAME_SECTION) {
		int ret;
		check_write();
		check_argc(argc, 2, 2);
		ret = git_config_rename_section_in_file(given_config_source.file,
							argv[0], argv[1]);
		if (ret < 0)
			return ret;
		if (ret == 0)
			die("No such section!");
	}
	else if (actions == ACTION_REMOVE_SECTION) {
		int ret;
		check_write();
		check_argc(argc, 1, 1);
		ret = git_config_rename_section_in_file(given_config_source.file,
							argv[0], NULL);
		if (ret < 0)
			return ret;
		if (ret == 0)
			die("No such section!");
	}
	else if (actions == ACTION_GET_COLOR) {
		get_color(argv[0]);
	}
	else if (actions == ACTION_GET_COLORBOOL) {
		if (argc == 1)
			color_stdout_is_tty = git_config_bool("command line", argv[0]);
		return get_colorbool(argc != 0);
	}

	return 0;
}