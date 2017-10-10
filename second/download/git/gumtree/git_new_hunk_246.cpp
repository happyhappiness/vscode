	return new_path;
}

/* FIXME: move prefix to startup_info struct and get rid of this arg */
void trace_repo_setup(const char *prefix)
{
	static struct trace_key key = TRACE_KEY_INIT(SETUP);
	const char *git_work_tree;
	char cwd[PATH_MAX];

	if (!trace_want(&key))
		return;

	if (!getcwd(cwd, PATH_MAX))
		die("Unable to get current working directory");

	if (!(git_work_tree = get_git_work_tree()))
		git_work_tree = "(null)";

	if (!prefix)
		prefix = "(null)";

	trace_printf_key(&key, "setup: git_dir: %s\n", quote_crnl(get_git_dir()));
	trace_printf_key(&key, "setup: worktree: %s\n", quote_crnl(git_work_tree));
	trace_printf_key(&key, "setup: cwd: %s\n", quote_crnl(cwd));
	trace_printf_key(&key, "setup: prefix: %s\n", quote_crnl(prefix));
}

int trace_want(struct trace_key *key)
{
	return !!get_trace_fd(key);
}

#ifdef HAVE_CLOCK_GETTIME

static inline uint64_t highres_nanos(void)
{
	struct timespec ts;
	if (clock_gettime(CLOCK_MONOTONIC, &ts))
		return 0;
	return (uint64_t) ts.tv_sec * 1000000000 + ts.tv_nsec;
}

#elif defined (GIT_WINDOWS_NATIVE)

static inline uint64_t highres_nanos(void)
{
	static uint64_t high_ns, scaled_low_ns;
	static int scale;
	LARGE_INTEGER cnt;

	if (!scale) {
		if (!QueryPerformanceFrequency(&cnt))
			return 0;

		/* high_ns = number of ns per cnt.HighPart */
		high_ns = (1000000000LL << 32) / (uint64_t) cnt.QuadPart;

		/*
		 * Number of ns per cnt.LowPart is 10^9 / frequency (or
		 * high_ns >> 32). For maximum precision, we scale this factor
		 * so that it just fits within 32 bit (i.e. won't overflow if
		 * multiplied with cnt.LowPart).
		 */
		scaled_low_ns = high_ns;
		scale = 32;
		while (scaled_low_ns >= 0x100000000LL) {
			scaled_low_ns >>= 1;
			scale--;
		}
	}

	/* if QPF worked on initialization, we expect QPC to work as well */
	QueryPerformanceCounter(&cnt);

	return (high_ns * cnt.HighPart) +
	       ((scaled_low_ns * cnt.LowPart) >> scale);
}

#else
# define highres_nanos() 0
#endif

static inline uint64_t gettimeofday_nanos(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (uint64_t) tv.tv_sec * 1000000000 + tv.tv_usec * 1000;
}

/*
 * Returns nanoseconds since the epoch (01/01/1970), for performance tracing
 * (i.e. favoring high precision over wall clock time accuracy).
 */
inline uint64_t getnanotime(void)
{
	static uint64_t offset;
	if (offset > 1) {
		/* initialization succeeded, return offset + high res time */
		return offset + highres_nanos();
	} else if (offset == 1) {
		/* initialization failed, fall back to gettimeofday */
		return gettimeofday_nanos();
	} else {
		/* initialize offset if high resolution timer works */
		uint64_t now = gettimeofday_nanos();
		uint64_t highres = highres_nanos();
		if (highres)
			offset = now - highres;
		else
			offset = 1;
		return now;
	}
}

static uint64_t command_start_time;
static struct strbuf command_line = STRBUF_INIT;

static void print_command_performance_atexit(void)
{
	trace_performance_since(command_start_time, "git command:%s",
				command_line.buf);
}

void trace_command_performance(const char **argv)
{
	if (!trace_want(&trace_perf_key))
		return;

	if (!command_start_time)
		atexit(print_command_performance_atexit);

	strbuf_reset(&command_line);
	sq_quote_argv(&command_line, argv, 0);
	command_start_time = getnanotime();
}
