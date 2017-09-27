AP_DECLARE(void) ap_log_error(const char *file, int line, int level, 
                             apr_status_t status, const server_rec *s, 
                             const char *fmt, ...)
			    __attribute__((format(printf,6,7)));

/**
 * The second of the primary logging routines in Apache.  This uses 
 * a printf-like format to log messages to the error_log.
 * @param file The file in which this function is called
 * @param line The line number on which this function is called
 * @param level The level of this error message
 * @param status The status code from the previous command
 * @param p The pool which we are logging for
 * @param fmt The format string
