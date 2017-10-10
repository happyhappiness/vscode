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

void trace_disable(struct trace_key *key)
{
	normalize_trace_key(&key);

	if (key->need_close)
		close(key->fd);
	key->fd = 0;
	key->initialized = 1;
	key->need_close = 0;
}

static int prepare_trace_line(const char *file, int line,
			      struct trace_key *key, struct strbuf *buf)
{
	static struct trace_key trace_bare = TRACE_KEY_INIT(BARE);
	struct timeval tv;
	struct tm tm;
