			error_with_usage("Can't specify files with --stdin");
	} else {
		if (filei >= argc)
			error_with_usage("No file specified");
	}

	if (all_attrs) {
		check = NULL;
	} else {
		check = xcalloc(cnt, sizeof(*check));
		for (i = 0; i < cnt; i++) {
			const char *name;
			struct git_attr *a;
			name = argv[i];
			a = git_attr(name);
			if (!a)
				return error("%s: not a valid attribute name",
					name);
			check[i].attr = a;
		}
	}

	if (stdin_paths)
		check_attr_stdin_paths(prefix, cnt, check);
	else {
		for (i = filei; i < argc; i++)
			check_attr(prefix, cnt, check, argv[i]);
		maybe_flush_or_die(stdout, "attribute to stdout");
	}
	return 0;
}
