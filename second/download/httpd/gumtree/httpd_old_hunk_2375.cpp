 * @param module_index The module_index of the module generating this message
 * @param level The level of this error message
 * @param status The status code from the previous command
 * @param s The server on which we are logging
 * @param fmt The format string
 * @param ... The arguments to use to fill out fmt.
 * @note Use APLOG_MARK to fill out file and line
 * @note If a request_rec is available, use that with ap_log_rerror()
 * in preference to calling this function.  Otherwise, if a conn_rec is
 * available, use that with ap_log_cerror() in preference to calling
 * this function.
 * @warning It is VERY IMPORTANT that you not include any raw data from 
 * the network, such as the request-URI or request header fields, within 
 * the format string.  Doing so makes the server vulnerable to a 
 * denial-of-service attack and other messy behavior.  Instead, use a 
 * simple format string like "%s", followed by the string containing the 
 * untrusted data.
 */
#if __STDC_VERSION__ >= 199901L
/* need additional step to expand APLOG_MARK first */
#define ap_log_error(...) ap_log_error__(__VA_ARGS__)
/* need server_rec *sr = ... for the case if s is verbatim NULL */
#define ap_log_error__(file, line, mi, level, status, s, ...)           \
    do { server_rec *sr = s; if (APLOG_MODULE_IS_LEVEL(sr, mi, level))      \
             ap_log_error_(file, line, mi, level, status, sr, __VA_ARGS__); \
    } while(0)
#else
#define ap_log_error ap_log_error_
#endif
AP_DECLARE(void) ap_log_error_(const char *file, int line, int module_index,
                               int level, apr_status_t status,
                               const server_rec *s, const char *fmt, ...)
                              __attribute__((format(printf,7,8)));

/**
 * ap_log_perror() - log messages which are not related to a particular
 * request, connection, or virtual server.  This uses a printf-like
 * format to log messages to the error_log.
 * @param file The file in which this function is called
