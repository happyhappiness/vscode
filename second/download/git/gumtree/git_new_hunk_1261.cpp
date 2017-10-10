
int cmd_credential(int argc, const char **argv, const char *prefix)
{
	const char *op;
	struct credential c = CREDENTIAL_INIT;

	if (argc != 2 || !strcmp(argv[1], "-h"))
		usage(usage_msg);
	op = argv[1];

	if (credential_read(&c, stdin) < 0)
		die("unable to read credential from stdin");

	if (!strcmp(op, "fill")) {
		credential_fill(&c);
