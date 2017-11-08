static int get_trace_fd(struct trace_key *key)
{
	static struct trace_key trace_default = { "GIT_TRACE" };
	const char *trace;

	/* use default "GIT_TRACE" if NULL */
	if (!key)
		key = &trace_default;

	/* don't open twice */
	if (key->initialized)
		return key->fd;

	trace = getenv(key->key);

	if (!trace || !strcmp(trace, "") ||
	    !strcmp(trace, "0") || !strcasecmp(trace, "false"))
		key->fd = 0;
	else if (!strcmp(trace, "1") || !strcasecmp(trace, "true"))
		key->fd = STDERR_FILENO;
	else if (strlen(trace) == 1 && isdigit(*trace))
		key->fd = atoi(trace);
	else if (is_absolute_path(trace)) {
		int fd = open(trace, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd == -1) {
			fprintf(stderr,
				"Could not open '%s' for tracing: %s\n"
				"Defaulting to tracing on stderr...\n",
				trace, strerror(errno));
			key->fd = STDERR_FILENO;
		} else {
			key->fd = fd;
			key->need_close = 1;
		}
	} else {
		fprintf(stderr, "What does '%s' for %s mean?\n"
			"If you want to trace into a file, then please set "
			"%s to an absolute pathname (starting with /).\n"
			"Defaulting to tracing on stderr...\n",
			trace, key->key, key->key);
		key->fd = STDERR_FILENO;
	}

	key->initialized = 1;
	return key->fd;
}