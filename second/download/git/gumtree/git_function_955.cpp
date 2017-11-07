static NORETURN void BUG_vfl(const char *file, int line, const char *fmt, va_list params)
{
	char prefix[256];

	/* truncation via snprintf is OK here */
	if (file)
		snprintf(prefix, sizeof(prefix), "BUG: %s:%d: ", file, line);
	else
		snprintf(prefix, sizeof(prefix), "BUG: ");

	vreportf(prefix, fmt, params);
	abort();
}