
static void rp_error(const char *err, ...) __attribute__((format (printf, 1, 2)));
static void rp_warning(const char *err, ...) __attribute__((format (printf, 1, 2)));

static void report_message(const char *prefix, const char *err, va_list params)
{
	int sz = strlen(prefix);
	char msg[4096];

	strncpy(msg, prefix, sz);
	sz += vsnprintf(msg + sz, sizeof(msg) - sz, err, params);
	if (sz > (sizeof(msg) - 1))
		sz = sizeof(msg) - 1;
	msg[sz++] = '\n';

	if (use_sideband)
