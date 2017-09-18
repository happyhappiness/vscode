AP_DECLARE(void) ap_log_perror(const char *file, int line, int level, 
                             apr_status_t status, apr_pool_t *p, 
                             const char *fmt, ...)
			    __attribute__((format(printf,6,7)));

/**
 * ap_log_rerror() - log messages which are related to a particular
 * request.  This uses a a printf-like format to log messages to the
 * error_log.
 * @param file The file in which this function is called
 * @param line The line number on which this function is called
 * @param level The level of this error message
 * @param status The status code from the previous command
 * @param r The request which we are logging for
 * @param fmt The format string
 * @param ... The arguments to use to fill out fmt.
 * @tip Use APLOG_MARK to fill out file and line
 * @warning It is VERY IMPORTANT that you not include any raw data from 
 * the network, such as the request-URI or request header fields, within 
 * the format string.  Doing so makes the server vulnerable to a 
 * denial-of-service attack and other messy behavior.  Instead, use a 
 * simple format string like "%s", followed by the string containing the 
 * untrusted data.
 * @deffunc void ap_log_rerror(const char *file, int line, int level, apr_status_t status, const request_rec *r, const char *fmt, ...)
 */
AP_DECLARE(void) ap_log_rerror(const char *file, int line, int level, 
                               apr_status_t status, const request_rec *r, 
                               const char *fmt, ...)
			    __attribute__((format(printf,6,7)));

/**
 * ap_log_cerror() - log messages which are related to a particular
 * connection.  This uses a a printf-like format to log messages to the
 * error_log.
 * @param file The file in which this function is called
 * @param line The line number on which this function is called
 * @param level The level of this error message
 * @param status The status code from the previous command
 * @param c The connection which we are logging for
 * @param fmt The format string
 * @param ... The arguments to use to fill out fmt.
 * @tip Use APLOG_MARK to fill out file and line
 * @tip If a request_rec is available, use that with ap_log_rerror()
 * in preference to calling this function.
 * @warning It is VERY IMPORTANT that you not include any raw data from 
 * the network, such as the request-URI or request header fields, within 
 * the format string.  Doing so makes the server vulnerable to a 
 * denial-of-service attack and other messy behavior.  Instead, use a 
 * simple format string like "%s", followed by the string containing the 
 * untrusted data.
 * @note ap_log_cerror() is available starting with Apache 2.0.55.
 * @deffunc void ap_log_cerror(const char *file, int line, int level, apr_status_t status, const conn_rec *c, const char *fmt, ...)
 */
AP_DECLARE(void) ap_log_cerror(const char *file, int line, int level, 
                               apr_status_t status, const conn_rec *c, 
                               const char *fmt, ...)
			    __attribute__((format(printf,6,7)));

/**
 * Convert stderr to the error log
 * @param s The current server
 * @deffunc void ap_error_log2stderr(server_rec *s)
 */
AP_DECLARE(void) ap_error_log2stderr(server_rec *s);

