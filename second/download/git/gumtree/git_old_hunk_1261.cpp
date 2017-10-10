
int cmd_credential(int argc, const char **argv, const char *prefix)
{
	const char *op;
	struct credential c = CREDENTIAL_INIT;

	op = argv[1];
	if (!op)
		usage(usage_msg);

	if (credential_read(&c, stdin) < 0)
		die("unable to read credential from stdin");

	if (!strcmp(op, "fill")) {
		credential_fill(&c);
