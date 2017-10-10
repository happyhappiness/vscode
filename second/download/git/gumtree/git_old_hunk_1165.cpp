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

