			usage_with_options(blame_opt_usage, options);
		}
	} else {
		if (argc < 2)
			usage_with_options(blame_opt_usage, options);
		path = add_prefix(prefix, argv[argc - 1]);
		if (argc == 3 && !has_string_in_work_tree(path)) { /* (2b) */
			path = add_prefix(prefix, argv[1]);
			argv[1] = argv[2];
		}
		argv[argc - 1] = "--";

		setup_work_tree();
		if (!has_string_in_work_tree(path))
			die_errno("cannot stat path '%s'", path);
	}

	revs.disable_stdin = 1;
	setup_revisions(argc, argv, &revs, NULL);
	memset(&sb, 0, sizeof(sb));
