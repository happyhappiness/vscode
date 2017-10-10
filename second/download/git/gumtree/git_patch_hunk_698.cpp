 	if (!argc)
 		usage_with_options(builtin_rm_usage, builtin_rm_options);
 
 	if (!index_only)
 		setup_work_tree();
 
-	hold_locked_index(&lock_file, 1);
+	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);
 
 	if (read_cache() < 0)
 		die(_("index file corrupt"));
 
 	parse_pathspec(&pathspec, 0,
 		       PATHSPEC_PREFER_CWD |
