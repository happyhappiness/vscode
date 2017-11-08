int main(int argc, char **argv)
{
	const char * const usage[] = {
		"git credential-store [<options>] <action>",
		NULL
	};
	const char *op;
	struct credential c = CREDENTIAL_INIT;
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