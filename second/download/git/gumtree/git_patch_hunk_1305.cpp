 		exc_given = 1;
 
 	if (require_work_tree && !is_inside_work_tree())
 		setup_work_tree();
 
 	if (recurse_submodules)
-		compile_submodule_options(argv, &dir, show_tag);
+		repo_read_gitmodules(the_repository);
 
 	if (recurse_submodules &&
 	    (show_stage || show_deleted || show_others || show_unmerged ||
 	     show_killed || show_modified || show_resolve_undo || with_tree))
 		die("ls-files --recurse-submodules unsupported mode");
 
 	if (recurse_submodules && error_unmatch)
 		die("ls-files --recurse-submodules does not support "
 		    "--error-unmatch");
 
 	parse_pathspec(&pathspec, 0,
-		       PATHSPEC_PREFER_CWD |
-		       PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP,
+		       PATHSPEC_PREFER_CWD,
 		       prefix, argv);
 
 	/*
 	 * Find common prefix for all pathspec's
 	 * This is used as a performance optimization which unfortunately cannot
-	 * be done when recursing into submodules
+	 * be done when recursing into submodules because when a pathspec is
+	 * given which spans repository boundaries you can't simply remove the
+	 * submodule entry because the pathspec may match something inside the
+	 * submodule.
 	 */
 	if (recurse_submodules)
 		max_prefix = NULL;
 	else
 		max_prefix = common_prefix(&pathspec);
-	max_prefix_len = max_prefix ? strlen(max_prefix) : 0;
+	max_prefix_len = get_common_prefix_len(max_prefix);
+
+	prune_index(the_repository->index, max_prefix, max_prefix_len);
 
 	/* Treat unmatching pathspec elements as errors */
 	if (pathspec.nr && error_unmatch)
 		ps_matched = xcalloc(pathspec.nr, 1);
 
 	if ((dir.flags & DIR_SHOW_IGNORED) && !exc_given)
