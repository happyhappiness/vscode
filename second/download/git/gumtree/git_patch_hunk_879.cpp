 		usage_with_options(builtin_commit_usage, builtin_commit_options);
 
 	status_init_config(&s, git_commit_config);
 	status_format = STATUS_FORMAT_NONE; /* Ignore status.short */
 	s.colopts = 0;
 
-	if (get_sha1("HEAD", sha1))
+	if (get_sha1("HEAD", oid.hash))
 		current_head = NULL;
 	else {
-		current_head = lookup_commit_or_die(sha1, "HEAD");
+		current_head = lookup_commit_or_die(oid.hash, "HEAD");
 		if (parse_commit(current_head))
 			die(_("could not parse HEAD commit"));
 	}
 	verbose = -1; /* unspecified */
 	argc = parse_and_validate_options(argc, argv, builtin_commit_options,
 					  builtin_commit_usage,
