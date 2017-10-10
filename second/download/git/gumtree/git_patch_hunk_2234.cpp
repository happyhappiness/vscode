 	if (squash) {
 		if (fast_forward == FF_NO)
 			die(_("You cannot combine --squash with --no-ff."));
 		option_commit = 0;
 	}
 
-	if (!abort_current_merge) {
-		if (!argc) {
-			if (default_to_upstream)
-				argc = setup_with_upstream(&argv);
-			else
-				die(_("No commit specified and merge.defaultToUpstream not set."));
-		} else if (argc == 1 && !strcmp(argv[0], "-"))
-			argv[0] = "@{-1}";
+	if (!argc) {
+		if (default_to_upstream)
+			argc = setup_with_upstream(&argv);
+		else
+			die(_("No commit specified and merge.defaultToUpstream not set."));
+	} else if (argc == 1 && !strcmp(argv[0], "-")) {
+		argv[0] = "@{-1}";
 	}
+
 	if (!argc)
 		usage_with_options(builtin_merge_usage,
 			builtin_merge_options);
 
-	/*
-	 * This could be traditional "merge <msg> HEAD <commit>..."  and
-	 * the way we can tell it is to see if the second token is HEAD,
-	 * but some people might have misused the interface and used a
-	 * commit-ish that is the same as HEAD there instead.
-	 * Traditional format never would have "-m" so it is an
-	 * additional safety measure to check for it.
-	 */
-
-	if (!have_message && head_commit &&
-	    is_old_style_invocation(argc, argv, head_commit->object.sha1)) {
-		strbuf_addstr(&merge_msg, argv[0]);
-		head_arg = argv[1];
-		argv += 2;
-		argc -= 2;
-		remoteheads = collect_parents(head_commit, &head_subsumed, argc, argv);
-	} else if (!head_commit) {
+	if (!head_commit) {
 		struct commit *remote_head;
 		/*
 		 * If the merged head is a valid one there is no reason
 		 * to forbid "git merge" into a branch yet to be born.
 		 * We do the same for "git pull".
 		 */
-		if (argc != 1)
-			die(_("Can merge only exactly one commit into "
-				"empty head"));
 		if (squash)
 			die(_("Squash commit into empty head not supported yet"));
 		if (fast_forward == FF_NO)
 			die(_("Non-fast-forward commit does not make sense into "
 			    "an empty head"));
-		remoteheads = collect_parents(head_commit, &head_subsumed, argc, argv);
+		remoteheads = collect_parents(head_commit, &head_subsumed,
+					      argc, argv, NULL);
 		remote_head = remoteheads->item;
 		if (!remote_head)
 			die(_("%s - not something we can merge"), argv[0]);
+		if (remoteheads->next)
+			die(_("Can merge only exactly one commit into empty head"));
 		read_empty(remote_head->object.sha1, 0);
 		update_ref("initial pull", "HEAD", remote_head->object.sha1,
 			   NULL, 0, UPDATE_REFS_DIE_ON_ERR);
 		goto done;
-	} else {
-		struct strbuf merge_names = STRBUF_INIT;
+	}
 
+	/*
+	 * This could be traditional "merge <msg> HEAD <commit>..."  and
+	 * the way we can tell it is to see if the second token is HEAD,
+	 * but some people might have misused the interface and used a
+	 * commit-ish that is the same as HEAD there instead.
+	 * Traditional format never would have "-m" so it is an
+	 * additional safety measure to check for it.
+	 */
+	if (!have_message &&
+	    is_old_style_invocation(argc, argv, head_commit->object.sha1)) {
+		warning("old-style 'git merge <msg> HEAD <commit>' is deprecated.");
+		strbuf_addstr(&merge_msg, argv[0]);
+		head_arg = argv[1];
+		argv += 2;
+		argc -= 2;
+		remoteheads = collect_parents(head_commit, &head_subsumed,
+					      argc, argv, NULL);
+	} else {
 		/* We are invoked directly as the first-class UI. */
 		head_arg = "HEAD";
 
 		/*
 		 * All the rest are the commits being merged; prepare
 		 * the standard merge summary message to be appended
 		 * to the given message.
 		 */
-		remoteheads = collect_parents(head_commit, &head_subsumed, argc, argv);
-		for (p = remoteheads; p; p = p->next)
-			merge_name(merge_remote_util(p->item)->name, &merge_names);
-
-		if (!have_message || shortlog_len) {
-			struct fmt_merge_msg_opts opts;
-			memset(&opts, 0, sizeof(opts));
-			opts.add_title = !have_message;
-			opts.shortlog_len = shortlog_len;
-			opts.credit_people = (0 < option_edit);
-
-			fmt_merge_msg(&merge_names, &merge_msg, &opts);
-			if (merge_msg.len)
-				strbuf_setlen(&merge_msg, merge_msg.len - 1);
-		}
+		remoteheads = collect_parents(head_commit, &head_subsumed,
+					      argc, argv, &merge_msg);
 	}
 
 	if (!head_commit || !argc)
 		usage_with_options(builtin_merge_usage,
 			builtin_merge_options);
 
