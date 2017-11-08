int main(int argc, const char **argv)
{
	char *socket_path = NULL;
	int timeout = 900;
	const char *op;
	const char * const usage[] = {
		"git credential-cache [options] <action>",
		NULL
	};
	struct option options[] = {
		OPT_INTEGER(0, "timeout", &timeout,
			    "number of seconds to cache credentials"),
		OPT_STRING(0, "socket", &socket_path, "path",
			   "path of cache-daemon socket"),
		OPT_END()
	};

	argc = parse_options(argc, argv, NULL, options, usage, 0);
	if (!argc)
		usage_with_options(usage, options);
	op = argv[0];

	if (!socket_path)
		socket_path = expand_user_path("~/.git-credential-cache/socket");
	if (!socket_path)
		die("unable to find a suitable socket path; use --socket");

	if (!strcmp(op, "exit"))
		do_cache(socket_path, op, timeout, 0);
	else if (!strcmp(op, "get") || !strcmp(op, "erase"))
		do_cache(socket_path, op, timeout, FLAG_RELAY);
	else if (!strcmp(op, "store"))
		do_cache(socket_path, op, timeout, FLAG_RELAY|FLAG_SPAWN);
	else
		; /* ignore unknown operation */

	return 0;
}