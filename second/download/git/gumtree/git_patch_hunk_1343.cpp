 			 N_("don't check the working tree after merging")),
 		OPT__DRY_RUN(&opts.dry_run, N_("don't update the index or the work tree")),
 		OPT_BOOL(0, "no-sparse-checkout", &opts.skip_sparse_checkout,
 			 N_("skip applying sparse checkout filter")),
 		OPT_BOOL(0, "debug-unpack", &opts.debug_unpack,
 			 N_("debug unpack-trees")),
-		{ OPTION_CALLBACK, 0, "recurse-submodules", &recurse_submodules,
+		{ OPTION_CALLBACK, 0, "recurse-submodules", NULL,
 			    "checkout", "control recursive updating of submodules",
-			    PARSE_OPT_OPTARG, option_parse_recurse_submodules },
+			    PARSE_OPT_OPTARG, option_parse_recurse_submodules_worktree_updater },
 		OPT_END()
 	};
 
 	memset(&opts, 0, sizeof(opts));
 	opts.head_idx = -1;
 	opts.src_index = &the_index;
 	opts.dst_index = &the_index;
 
-	git_config(git_default_config, NULL);
+	git_config(git_read_tree_config, NULL);
 
 	argc = parse_options(argc, argv, unused_prefix, read_tree_options,
 			     read_tree_usage, 0);
 
-	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);
+	load_submodule_cache();
 
-	if (recurse_submodules != RECURSE_SUBMODULES_DEFAULT) {
-		gitmodules_config();
-		git_config(submodule_config, NULL);
-		set_config_update_recurse_submodules(RECURSE_SUBMODULES_ON);
-	}
+	hold_locked_index(&lock_file, LOCK_DIE_ON_ERROR);
 
 	prefix_set = opts.prefix ? 1 : 0;
 	if (1 < opts.merge + opts.reset + prefix_set)
 		die("Which one? -m, --reset, or --prefix?");
 
 	/*
