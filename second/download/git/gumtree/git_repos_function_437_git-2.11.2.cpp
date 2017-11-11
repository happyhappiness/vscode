int cmd_main(int argc, const char **argv)
{
	const char * const usage[] = {
		"git credential-store [<options>] <action>",
		NULL
	};
	const char *op;
	struct credential c = CREDENTIAL_INIT;
	struct string_list fns = STRING_LIST_INIT_DUP;
	char *file = NULL;
	struct option options[] = {
		OPT_STRING(0, "file", &file, "path",
			   "fetch and store credentials in <path>"),
		OPT_END()
	};

	umask(077);

	argc = parse_options(argc, (const char **)argv, NULL, options, usage, 0);
	if (argc != 1)
		usage_with_options(usage, options);
	op = argv[0];

	if (file) {
		string_list_append(&fns, file);
	} else {
		if ((file = expand_user_path("~/.git-credentials")))
			string_list_append_nodup(&fns, file);
		file = xdg_config_home("credentials");
		if (file)
			string_list_append_nodup(&fns, file);
	}
	if (!fns.nr)
		die("unable to set up default path; use --file");

	if (credential_read(&c, stdin) < 0)
		die("unable to read credential");

	if (!strcmp(op, "get"))
		lookup_credential(&fns, &c);
	else if (!strcmp(op, "erase"))
		remove_credential(&fns, &c);
	else if (!strcmp(op, "store"))
		store_credential(&fns, &c);
	else
		; /* Ignore unknown operation. */

	string_list_clear(&fns, 0);
	return 0;
}