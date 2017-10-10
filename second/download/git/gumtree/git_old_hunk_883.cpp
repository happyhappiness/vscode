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
