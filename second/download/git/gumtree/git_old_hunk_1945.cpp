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
