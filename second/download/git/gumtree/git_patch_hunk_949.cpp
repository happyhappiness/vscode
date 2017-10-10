 
 	argc = parse_options(argc, argv, unused_prefix, read_tree_options,
 			     read_tree_usage, 0);
 
 	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);
 
+	if (recurse_submodules != RECURSE_SUBMODULES_DEFAULT) {
+		gitmodules_config();
+		git_config(submodule_config, NULL);
+		set_config_update_recurse_submodules(RECURSE_SUBMODULES_ON);
+	}
+
 	prefix_set = opts.prefix ? 1 : 0;
 	if (1 < opts.merge + opts.reset + prefix_set)
 		die("Which one? -m, --reset, or --prefix?");
 
 	/*
 	 * NEEDSWORK
