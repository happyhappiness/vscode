static int prepare_trace_line(const char *file, int line,
			      struct trace_key *key, struct strbuf *buf)
{
	static struct trace_key trace_bare = TRACE_KEY_INIT(BARE);
	struct timeval tv;
	struct tm tm;
	time_t secs;

	if (!trace_want(key))
		return 0;

	set_try_to_free_routine(NULL);	/* is never reset */

	/* unit tests may want to disable additional trace output */
	if (trace_want(&trace_bare))
		return 1;

	/* print current timestamp */
	gettimeofday(&tv, NULL);
	secs = tv.tv_sec;
	localtime_r(&secs, &tm);
	strbuf_addf(buf, "%02d:%02d:%02d.%06ld ", tm.tm_hour, tm.tm_min,
		    tm.tm_sec, (long) tv.tv_usec);

#ifdef HAVE_VARIADIC_MACROS
	/* print file:line */
	strbuf_addf(buf, "%s:%d ", file, line);
	/* align trace output (column 40 catches most files names in git) */
	while (buf->len < 40)
		strbuf_addch(buf, ' ');
#endif

	return 1;
}