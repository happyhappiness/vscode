 * the network, such as the request-URI or request header fields, within 
 * the format string.  Doing so makes the server vulnerable to a 
 * denial-of-service attack and other messy behavior.  Instead, use a 
 * simple format string like "%s", followed by the string containing the 
 * untrusted data.
 */
AP_DECLARE(void) ap_log_cerror(const char *file, int line, int level, 
                               apr_status_t status, const conn_rec *c, 
                               const char *fmt, ...)
			    __attribute__((format(printf,6,7)));

/**
 * Convert stderr to the error log
 * @param s The current server
 */
AP_DECLARE(void) ap_error_log2stderr(server_rec *s);

/**
 * Log the current pid of the parent process
 * @param p The pool to use for logging
 * @param fname The name of the file to log to
 */
AP_DECLARE(void) ap_log_pid(apr_pool_t *p, const char *fname);

