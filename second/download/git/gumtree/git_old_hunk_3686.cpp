
	if (argc > 0) {
		repo = argv[0];
		set_refspecs(argv + 1, argc - 1, repo);
	}

	rc = do_push(repo, flags);
	if (rc == -1)
		usage_with_options(push_usage, options);
	else
		return rc;
}
