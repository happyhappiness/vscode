/*
 * Prints the SSL library error information.
 */
void ssl_log_ssl_error(const char *file, int line, int level, server_rec *s)
{
    unsigned long e;

    while ((e = ERR_get_error())) {
        const char *annotation;
        char err[256];

        ERR_error_string_n(e, err, sizeof err);
        annotation = ssl_log_annotation(err);

        if (annotation) {
            ap_log_error(file, line, level, 0, s,
                         "SSL Library Error: %lu %s %s",
                         e, err, annotation);
        }
        else {
            ap_log_error(file, line, level, 0, s,
                         "SSL Library Error: %lu %s",
                         e, err);
        }
    }
}
