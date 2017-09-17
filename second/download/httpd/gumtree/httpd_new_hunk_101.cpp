
API_EXPORT(void) ap_error_log2stderr (server_rec *s) {
    if(fileno(s->error_log) != STDERR_FILENO)
        dup2(fileno(s->error_log),STDERR_FILENO);
}

static void log_error_core (const char *file, int line, int level,
			   const server_rec *s, const request_rec *r,
			   const char *fmt, va_list args)
{
    char errstr[MAX_STRING_LEN];
    size_t len;
    int save_errno = errno;
    FILE *logf;

    if (s == NULL) {
