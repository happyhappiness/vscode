	else if (!lstat(dest_path[0], &st) &&
			S_ISDIR(st.st_mode)) {
		dest_path[0] = add_slash(dest_path[0]);
		destination = internal_copy_pathspec(dest_path[0], argv, argc, DUP_BASENAME);
	} else {
		if (argc != 1)
			die("destination '%s' is not a directory", dest_path[0]);
		destination = dest_path;
	}

	/* Checking */
	for (i = 0; i < argc; i++) {
		const char *src = source[i], *dst = destination[i];
