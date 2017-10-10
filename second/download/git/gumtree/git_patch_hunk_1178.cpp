 		for_each_glob_ref(handle_one_ref, optarg, &cb);
 		clear_ref_exclusion(&revs->ref_excludes);
 		return argcount;
 	} else if ((argcount = parse_long_opt("exclude", argv, &optarg))) {
 		add_ref_exclusion(&revs->ref_excludes, optarg);
 		return argcount;
-	} else if (starts_with(arg, "--branches=")) {
+	} else if (skip_prefix(arg, "--branches=", &optarg)) {
 		struct all_refs_cb cb;
 		init_all_refs_cb(&cb, revs, *flags);
-		for_each_glob_ref_in(handle_one_ref, arg + 11, "refs/heads/", &cb);
+		for_each_glob_ref_in(handle_one_ref, optarg, "refs/heads/", &cb);
 		clear_ref_exclusion(&revs->ref_excludes);
-	} else if (starts_with(arg, "--tags=")) {
+	} else if (skip_prefix(arg, "--tags=", &optarg)) {
 		struct all_refs_cb cb;
 		init_all_refs_cb(&cb, revs, *flags);
-		for_each_glob_ref_in(handle_one_ref, arg + 7, "refs/tags/", &cb);
+		for_each_glob_ref_in(handle_one_ref, optarg, "refs/tags/", &cb);
 		clear_ref_exclusion(&revs->ref_excludes);
-	} else if (starts_with(arg, "--remotes=")) {
+	} else if (skip_prefix(arg, "--remotes=", &optarg)) {
 		struct all_refs_cb cb;
 		init_all_refs_cb(&cb, revs, *flags);
-		for_each_glob_ref_in(handle_one_ref, arg + 10, "refs/remotes/", &cb);
+		for_each_glob_ref_in(handle_one_ref, optarg, "refs/remotes/", &cb);
 		clear_ref_exclusion(&revs->ref_excludes);
 	} else if (!strcmp(arg, "--reflog")) {
 		add_reflogs_to_pending(revs, *flags);
 	} else if (!strcmp(arg, "--indexed-objects")) {
 		add_index_objects_to_pending(revs, *flags);
 	} else if (!strcmp(arg, "--not")) {
 		*flags ^= UNINTERESTING | BOTTOM;
 	} else if (!strcmp(arg, "--no-walk")) {
 		revs->no_walk = REVISION_WALK_NO_WALK_SORTED;
-	} else if (starts_with(arg, "--no-walk=")) {
+	} else if (skip_prefix(arg, "--no-walk=", &optarg)) {
 		/*
 		 * Detached form ("--no-walk X" as opposed to "--no-walk=X")
 		 * not allowed, since the argument is optional.
 		 */
-		if (!strcmp(arg + 10, "sorted"))
+		if (!strcmp(optarg, "sorted"))
 			revs->no_walk = REVISION_WALK_NO_WALK_SORTED;
-		else if (!strcmp(arg + 10, "unsorted"))
+		else if (!strcmp(optarg, "unsorted"))
 			revs->no_walk = REVISION_WALK_NO_WALK_UNSORTED;
 		else
 			return error("invalid argument to --no-walk");
 	} else if (!strcmp(arg, "--do-walk")) {
 		revs->no_walk = 0;
 	} else {
