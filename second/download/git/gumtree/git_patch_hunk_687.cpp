 
 	argc = parse_options(argc, argv, prefix, builtin_mv_options,
 			     builtin_mv_usage, 0);
 	if (--argc < 1)
 		usage_with_options(builtin_mv_usage, builtin_mv_options);
 
-	hold_locked_index(&lock_file, 1);
+	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);
 	if (read_cache() < 0)
 		die(_("index file corrupt"));
 
-	source = internal_copy_pathspec(prefix, argv, argc, 0);
+	source = internal_prefix_pathspec(prefix, argv, argc, 0);
 	modes = xcalloc(argc, sizeof(enum update_mode));
 	/*
 	 * Keep trailing slash, needed to let
 	 * "git mv file no-such-dir/" error out, except in the case
 	 * "git mv directory no-such-dir/".
 	 */
 	flags = KEEP_TRAILING_SLASH;
 	if (argc == 1 && is_directory(argv[0]) && !is_directory(argv[1]))
 		flags = 0;
-	dest_path = internal_copy_pathspec(prefix, argv + argc, 1, flags);
+	dest_path = internal_prefix_pathspec(prefix, argv + argc, 1, flags);
 	submodule_gitfile = xcalloc(argc, sizeof(char *));
 
 	if (dest_path[0][0] == '\0')
 		/* special case: "." was normalized to "" */
-		destination = internal_copy_pathspec(dest_path[0], argv, argc, DUP_BASENAME);
+		destination = internal_prefix_pathspec(dest_path[0], argv, argc, DUP_BASENAME);
 	else if (!lstat(dest_path[0], &st) &&
 			S_ISDIR(st.st_mode)) {
 		dest_path[0] = add_slash(dest_path[0]);
-		destination = internal_copy_pathspec(dest_path[0], argv, argc, DUP_BASENAME);
+		destination = internal_prefix_pathspec(dest_path[0], argv, argc, DUP_BASENAME);
 	} else {
 		if (argc != 1)
 			die(_("destination '%s' is not a directory"), dest_path[0]);
 		destination = dest_path;
 	}
 
