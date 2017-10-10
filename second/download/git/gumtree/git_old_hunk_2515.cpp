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
