static int get_trace_fd(struct trace_key *key)
{
	const char *trace;

	normalize_trace_key(&key);

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
			warning("could not open '%s' for tracing: %s",
				trace, strerror(errno));
			trace_disable(key);
		} else {
			key->fd = fd;
			key->need_close = 1;
		}
	} else {
		warning("unknown trace value for '%s': %s\n"
			"         If you want to trace into a file, then please set %s\n"
			"         to an absolute pathname (starting with /)",
			key->key, trace, key->key);
		trace_disable(key);
	}

	key->initialized = 1;
	return key->fd;
}