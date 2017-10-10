
	argc = parse_options(argc, (const char **)argv, NULL, options, usage, 0);
	if (argc != 1)
		usage_with_options(usage, options);
	op = argv[0];

	if (!file)
		file = expand_user_path("~/.git-credentials");
	if (!file)
		die("unable to set up default path; use --file");

	if (credential_read(&c, stdin) < 0)
		die("unable to read credential");

	if (!strcmp(op, "get"))
		lookup_credential(file, &c);
	else if (!strcmp(op, "erase"))
		remove_credential(file, &c);
	else if (!strcmp(op, "store"))
		store_credential(file, &c);
	else
		; /* Ignore unknown operation. */

	return 0;
}
