					  given_config_source.file);
			else
				die("error processing config file(s)");
		}
	}
	else if (actions == ACTION_EDIT) {
		check_argc(argc, 0, 0);
		if (!given_config_source.file && nongit)
			die("not in a git directory");
		if (given_config_source.use_stdin)
			die("editing stdin is not supported");
		if (given_config_source.blob)
			die("editing blobs is not supported");
		git_config(git_default_config, NULL);
		launch_editor(given_config_source.file ?
			      given_config_source.file : git_path("config"),
			      NULL, NULL);
	}
	else if (actions == ACTION_SET) {
		int ret;
		check_write();
		check_argc(argc, 2, 2);
		value = normalize_value(argv[0], argv[1]);
