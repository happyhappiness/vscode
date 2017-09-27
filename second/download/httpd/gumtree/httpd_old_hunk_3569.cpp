                                 int level, apr_status_t status,
                                 const conn_rec *c, const server_rec *s,
                                 const char *fmt, ...)
                             __attribute__((format(printf,8,9)));
#endif

/**
 * Convert stderr to the error log
 * @param s The current server
 */
AP_DECLARE(void) ap_error_log2stderr(server_rec *s);

