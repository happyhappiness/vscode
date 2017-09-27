 * @param level The level of this error message
 * @param module_index The module_index of the module generating this message
 * @param status The status code from the previous command
 * @param c The connection which we are logging for
 * @param fmt The format string
 * @param ... The arguments to use to fill out fmt.
 * @note ap_log_cerror is implemented as a macro
 * @note Use APLOG_MARK to fill out file, line, and module_index
 * @note If a request_rec is available, use that with ap_log_rerror()
 * in preference to calling this function.
 * @warning It is VERY IMPORTANT that you not include any raw data from
 * the network, such as the request-URI or request header fields, within
 * the format string.  Doing so makes the server vulnerable to a
 * denial-of-service attack and other messy behavior.  Instead, use a
 * simple format string like "%s", followed by the string containing the
 * untrusted data.
 */
#ifdef DOXYGEN
AP_DECLARE(void) ap_log_cerror(const char *file, int line, int module_index,
                               int level, apr_status_t status,
                               const conn_rec *c, const char *fmt, ...);
#else
#if __STDC_VERSION__ >= 199901L
/* need additional step to expand APLOG_MARK first */
#define ap_log_cerror(...) ap_log_cerror__(__VA_ARGS__)
#define ap_log_cerror__(file, line, mi, level, status, c, ...)              \
    do { if (APLOG_C_MODULE_IS_LEVEL(c, mi, level))                         \
             ap_log_cerror_(file, line, mi, level, status, c, __VA_ARGS__); \
    } while(0)
#else
#define ap_log_cerror ap_log_cerror_
#endif
AP_DECLARE(void) ap_log_cerror_(const char *file, int line, int module_index,
                                int level, apr_status_t status,
                                const conn_rec *c, const char *fmt, ...)
                                __attribute__((format(printf,7,8)));
#endif

/**
 * ap_log_cserror() - log messages which are related to a particular
 * connection and to a vhost other than c->base_server.  This uses a
 * printf-like format to log messages to the error_log.
 * @param file The file in which this function is called
