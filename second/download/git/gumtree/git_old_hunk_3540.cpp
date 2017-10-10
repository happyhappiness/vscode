		die(_("index file corrupt"));

	source = internal_copy_pathspec(prefix, argv, argc, 0);
	modes = xcalloc(argc, sizeof(enum update_mode));
	/*
	 * Keep trailing slash, needed to let
	 * "git mv file no-such-dir/" error out.
	 */
	dest_path = internal_copy_pathspec(prefix, argv + argc, 1,
					   KEEP_TRAILING_SLASH);
	submodule_gitfile = xcalloc(argc, sizeof(char *));

	if (dest_path[0][0] == '\0')
		/* special case: "." was normalized to "" */
		destination = internal_copy_pathspec(dest_path[0], argv, argc, DUP_BASENAME);
	else if (!lstat(dest_path[0], &st) &&
