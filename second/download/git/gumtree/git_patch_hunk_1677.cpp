 		usage_with_options(builtin_branch_usage, options);
 
 	git_config(git_branch_config, NULL);
 
 	track = git_branch_track;
 
-	head = resolve_refdup("HEAD", head_sha1, 0, NULL);
+	head = resolve_refdup("HEAD", 0, head_sha1, NULL);
 	if (!head)
 		die(_("Failed to resolve HEAD as a valid ref."));
-	if (!strcmp(head, "HEAD")) {
+	if (!strcmp(head, "HEAD"))
 		detached = 1;
-	} else {
-		if (!starts_with(head, "refs/heads/"))
-			die(_("HEAD not found below refs/heads!"));
-		head += 11;
-	}
+	else if (!skip_prefix(head, "refs/heads/", &head))
+		die(_("HEAD not found below refs/heads!"));
 	hashcpy(merge_filter_ref, head_sha1);
 
 
 	argc = parse_options(argc, argv, prefix, options, builtin_branch_usage,
 			     0);
 
