 		rename *= 2;
 	}
 
 	if (delete) {
 		if (!argc)
 			die(_("branch name required"));
-		return delete_branches(argc, argv, delete > 1, kinds, quiet);
+		return delete_branches(argc, argv, delete > 1, filter.kind, quiet);
 	} else if (list) {
-		int ret = print_ref_list(kinds, detached, verbose, abbrev,
-					 with_commit, argv);
+		/*  git branch --local also shows HEAD when it is detached */
+		if ((filter.kind & FILTER_REFS_BRANCHES) && filter.detached)
+			filter.kind |= FILTER_REFS_DETACHED_HEAD;
+		filter.name_patterns = argv;
+		print_ref_list(&filter, sorting);
 		print_columns(&output, colopts, NULL);
 		string_list_clear(&output, 0);
-		return ret;
+		return 0;
 	}
 	else if (edit_description) {
 		const char *branch_name;
 		struct strbuf branch_ref = STRBUF_INIT;
 
 		if (!argc) {
-			if (detached)
+			if (filter.detached)
 				die(_("Cannot give description to detached HEAD"));
 			branch_name = head;
 		} else if (argc == 1)
 			branch_name = argv[0];
 		else
 			die(_("cannot edit description of more than one branch"));
