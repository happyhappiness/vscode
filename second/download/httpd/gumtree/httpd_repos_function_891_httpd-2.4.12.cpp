void ssl_log_ssl_error(const char *file, int line, int level, server_rec *s)
{
    unsigned long e;
    const char *data;
    int flags;

    while ((e = ERR_peek_error_line_data(NULL, NULL, &data, &flags))) {
        const char *annotation;
        char err[256];

        if (!(flags & ERR_TXT_STRING)) {
            data = NULL;
        }

        ERR_error_string_n(e, err, sizeof err);
        annotation = ssl_log_annotation(err);

        ap_log_error(file, line, APLOG_MODULE_INDEX, level, 0, s,
                     "SSL Library Error: %s%s%s%s%s%s",
                     /* %s */
                     err,
                     /* %s%s%s */
                     data ? " (" : "", data ? data : "", data ? ")" : "",
                     /* %s%s */
                     annotation ? " -- " : "",
                     annotation ? annotation : "");

        /* Pop the error off the stack: */
        ERR_get_error();
    }
}