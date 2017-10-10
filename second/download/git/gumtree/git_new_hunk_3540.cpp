		die(_("index file corrupt"));

	source = internal_copy_pathspec(prefix, argv, argc, 0);
	modes = xcalloc(argc, sizeof(enum update_mode));
	/*
	 * Keep trailing slash, needed to let
	 * "git mv file no-such-dir/" error out, except in the case
	 * "git mv directory no-such-dir/".
	 */
	flags = KEEP_TRAILING_SLASH;
	if (argc == 1 && is_directory(argv[0]) && !is_directory(argv[1]))
		flags = 0;
	dest_path = internal_copy_pathspec(prefix, argv + argc, 1, flags);
	submodule_gitfile = xcalloc(argc, sizeof(char *));

	if (dest_path[0][0] == '\0')
		/* special case: "." was normalized to "" */
		destination = internal_copy_pathspec(dest_path[0], argv, argc, DUP_BASENAME);
	else if (!lstat(dest_path[0], &st) &&
