 		return 0;
 	}
 
 	if (read_cache() < 0)
 		die(_("index file corrupt"));
 
+	die_in_unpopulated_submodule(&the_index, prefix);
+
 	/*
 	 * Check the "pathspec '%s' did not match any files" block
 	 * below before enabling new magic.
 	 */
 	parse_pathspec(&pathspec, 0,
 		       PATHSPEC_PREFER_FULL |
-		       PATHSPEC_SYMLINK_LEADING_PATH |
-		       PATHSPEC_STRIP_SUBMODULE_SLASH_EXPENSIVE,
+		       PATHSPEC_SYMLINK_LEADING_PATH,
 		       prefix, argv);
 
+	die_path_inside_submodule(&the_index, &pathspec);
+
 	if (add_new_files) {
 		int baselen;
 
 		/* Set up the default git porcelain excludes */
 		memset(&dir, 0, sizeof(dir));
 		if (!ignored_too) {
 			dir.flags |= DIR_COLLECT_IGNORED;
 			setup_standard_excludes(&dir);
 		}
 
 		/* This picks up the paths that are not tracked */
-		baselen = fill_directory(&dir, &pathspec);
+		baselen = fill_directory(&dir, &the_index, &pathspec);
 		if (pathspec.nr)
 			seen = prune_directory(&dir, &pathspec, baselen);
 	}
 
 	if (refresh_only) {
 		refresh(verbose, &pathspec);
