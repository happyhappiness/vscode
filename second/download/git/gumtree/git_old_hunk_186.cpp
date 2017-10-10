	for (i = 1; i < global_argc; i++) {
		const char *a = global_argv[i];

		if (*a != '-' || !strcmp(a, "--"))
			break;

		if (parse_one_option(a + 2))
			continue;

		if (parse_one_feature(a + 2, 0))
			continue;

		if (starts_with(a + 2, "cat-blob-fd=")) {
			option_cat_blob_fd(a + 2 + strlen("cat-blob-fd="));
			continue;
		}

		die("unknown option %s", a);
	}
	if (i != global_argc)
		usage(fast_import_usage);

	seen_data_command = 1;
	if (import_marks_file)
