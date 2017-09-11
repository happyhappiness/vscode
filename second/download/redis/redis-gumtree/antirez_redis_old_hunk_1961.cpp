
JEMALLOC_ATTR(format(printf, 2, 3))
static bool
prof_printf(bool propagate_err, const char *format, ...)
{
	bool ret;
	va_list ap;
