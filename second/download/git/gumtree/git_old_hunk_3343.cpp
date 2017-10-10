		current_head = NULL;
	else {
		current_head = lookup_commit_or_die(sha1, "HEAD");
		if (parse_commit(current_head))
			die(_("could not parse HEAD commit"));
	}
	argc = parse_and_validate_options(argc, argv, builtin_commit_options,
					  builtin_commit_usage,
					  prefix, current_head, &s);
	if (dry_run)
		return dry_run_commit(argc, argv, prefix, current_head, &s);
	index_file = prepare_index(argc, argv, prefix, current_head, 0);

	/* Set up everything for writing the commit object.  This includes
	   running hooks, writing the trees, and interacting with the user.  */
