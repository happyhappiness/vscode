		usage_with_options(builtin_branch_usage, options);

	git_config(git_branch_config, NULL);

	track = git_branch_track;

	head = resolve_refdup("HEAD", head_sha1, 0, NULL);
	if (!head)
		die(_("Failed to resolve HEAD as a valid ref."));
	if (!strcmp(head, "HEAD")) {
		detached = 1;
	} else {
		if (!starts_with(head, "refs/heads/"))
			die(_("HEAD not found below refs/heads!"));
		head += 11;
	}
	hashcpy(merge_filter_ref, head_sha1);


	argc = parse_options(argc, argv, prefix, options, builtin_branch_usage,
			     0);

