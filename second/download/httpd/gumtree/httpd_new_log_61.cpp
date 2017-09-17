T(void) ap_log_error (const char *file, int line, int level,
			      const server_rec *s, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, level, s, NULL, fmt, args);
    va_end(args);
}

API_EXPORT(void) ap_log_rerror(const char *file, int line, int level,
			       const request_rec *r, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    log_error_core(file, line, level, r->server, r, fmt, args);
    if (ap_table_get(r->notes, "error-notes") == NULL) {
	char errstr[MAX_STRING_LEN];

	ap_vsnprintf(errstr, sizeof(errstr), fmt, args);
	ap_table_set(r->notes, "error-notes", errstr);
    }
    va_end(args);