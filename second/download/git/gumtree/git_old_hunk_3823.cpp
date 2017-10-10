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

void trace_disable(struct trace_key *key)
{
	if (key->need_close)
		close(key->fd);
	key->fd = 0;
	key->initialized = 1;
	key->need_close = 0;
}

static const char err_msg[] = "Could not trace into fd given by "
	"GIT_TRACE environment variable";

static int prepare_trace_line(const char *file, int line,
			      struct trace_key *key, struct strbuf *buf)
{
	static struct trace_key trace_bare = TRACE_KEY_INIT(BARE);
	struct timeval tv;
	struct tm tm;
