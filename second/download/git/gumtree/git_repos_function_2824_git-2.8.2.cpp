static void run_service(const char **argv, int buffer_input)
{
	const char *encoding = getenv("HTTP_CONTENT_ENCODING");
	const char *user = getenv("REMOTE_USER");
	const char *host = getenv("REMOTE_ADDR");
	int gzipped_request = 0;
	struct child_process cld = CHILD_PROCESS_INIT;

	if (encoding && !strcmp(encoding, "gzip"))
		gzipped_request = 1;
	else if (encoding && !strcmp(encoding, "x-gzip"))
		gzipped_request = 1;

	if (!user || !*user)
		user = "anonymous";
	if (!host || !*host)
		host = "(none)";

	if (!getenv("GIT_COMMITTER_NAME"))
		argv_array_pushf(&cld.env_array, "GIT_COMMITTER_NAME=%s", user);
	if (!getenv("GIT_COMMITTER_EMAIL"))
		argv_array_pushf(&cld.env_array,
				 "GIT_COMMITTER_EMAIL=%s@http.%s", user, host);

	cld.argv = argv;
	if (buffer_input || gzipped_request)
		cld.in = -1;
	cld.git_cmd = 1;
	if (start_command(&cld))
		exit(1);

	close(1);
	if (gzipped_request)
		inflate_request(argv[0], cld.in, buffer_input);
	else if (buffer_input)
		copy_request(argv[0], cld.in);
	else
		close(0);

	if (finish_command(&cld))
		exit(1);
}