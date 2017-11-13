static int get_trace_fd(const char *key, int *need_close)
{
	char *trace = getenv(key);

	if (!trace || !strcmp(trace, "") ||
	    !strcmp(trace, "0") || !strcasecmp(trace, "false"))
		return 0;
	if (!strcmp(trace, "1") || !strcasecmp(trace, "true"))
		return STDERR_FILENO;
	if (strlen(trace) == 1 && isdigit(*trace))
		return atoi(trace);
	if (is_absolute_path(trace)) {
		int fd = open(trace, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd == -1) {
			fprintf(stderr,
				"Could not open '%s' for tracing: %s\n"
				"Defaulting to tracing on stderr...\n",
				trace, strerror(errno));
			return STDERR_FILENO;
		}
		*need_close = 1;
		return fd;
	}

	fprintf(stderr, "What does '%s' for %s mean?\n", trace, key);
	fprintf(stderr, "If you want to trace into a file, "
		"then please set %s to an absolute pathname "
		"(starting with /).\n", key);
	fprintf(stderr, "Defaulting to tracing on stderr...\n");

	return STDERR_FILENO;
}