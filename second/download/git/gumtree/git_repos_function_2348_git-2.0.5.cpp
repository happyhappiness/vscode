static void run_service(const char **argv)
{
	const char *encoding = getenv("HTTP_CONTENT_ENCODING");
	const char *user = getenv("REMOTE_USER");
	const char *host = getenv("REMOTE_ADDR");
	struct argv_array env = ARGV_ARRAY_INIT;
	int gzipped_request = 0;
	struct child_process cld;

	if (encoding && !strcmp(encoding, "gzip"))
		gzipped_request = 1;
	else if (encoding && !strcmp(encoding, "x-gzip"))
		gzipped_request = 1;

	if (!user || !*user)
		user = "anonymous";
	if (!host || !*host)
		host = "(none)";

	if (!getenv("GIT_COMMITTER_NAME"))
		argv_array_pushf(&env, "GIT_COMMITTER_NAME=%s", user);
	if (!getenv("GIT_COMMITTER_EMAIL"))
		argv_array_pushf(&env, "GIT_COMMITTER_EMAIL=%s@http.%s",
				 user, host);

	memset(&cld, 0, sizeof(cld));
	cld.argv = argv;
	cld.env = env.argv;
	if (gzipped_request)
		cld.in = -1;
	cld.git_cmd = 1;
	if (start_command(&cld))
		exit(1);

	close(1);
	if (gzipped_request)
		inflate_request(argv[0], cld.in);
	else
		close(0);

	if (finish_command(&cld))
		exit(1);
	argv_array_clear(&env);
}