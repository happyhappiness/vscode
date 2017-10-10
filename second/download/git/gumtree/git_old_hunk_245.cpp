 */

#include "cache.h"
#include "quote.h"

/* Get a trace file descriptor from "key" env variable. */
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

static const char err_msg[] = "Could not trace into fd given by "
	"GIT_TRACE environment variable";

static void trace_vprintf(const char *key, const char *fmt, va_list ap)
{
	struct strbuf buf = STRBUF_INIT;

	if (!trace_want(key))
		return;

	set_try_to_free_routine(NULL);	/* is never reset */
	strbuf_vaddf(&buf, fmt, ap);
	trace_strbuf(key, &buf);
	strbuf_release(&buf);
}

__attribute__((format (printf, 2, 3)))
void trace_printf_key(const char *key, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	trace_vprintf(key, fmt, ap);
	va_end(ap);
}

void trace_printf(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	trace_vprintf("GIT_TRACE", fmt, ap);
	va_end(ap);
}

void trace_strbuf(const char *key, const struct strbuf *buf)
{
	int fd, need_close = 0;

	fd = get_trace_fd(key, &need_close);
	if (!fd)
		return;

	write_or_whine_pipe(fd, buf->buf, buf->len, err_msg);

	if (need_close)
		close(fd);
}

void trace_argv_printf(const char **argv, const char *fmt, ...)
{
	struct strbuf buf = STRBUF_INIT;
	va_list ap;
	int fd, need_close = 0;

	fd = get_trace_fd("GIT_TRACE", &need_close);
	if (!fd)
		return;

	set_try_to_free_routine(NULL);	/* is never reset */
	va_start(ap, fmt);
	strbuf_vaddf(&buf, fmt, ap);
	va_end(ap);

	sq_quote_argv(&buf, argv, 0);
	strbuf_addch(&buf, '\n');
	write_or_whine_pipe(fd, buf.buf, buf.len, err_msg);
	strbuf_release(&buf);

	if (need_close)
		close(fd);
}

static const char *quote_crnl(const char *path)
{
	static char new_path[PATH_MAX];
	const char *p2 = path;
	char *p1 = new_path;

