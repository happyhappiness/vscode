#define ap_log_perror ap_log_perror_
#endif
AP_DECLARE(void) ap_log_perror_(const char *file, int line, int module_index,
                                int level, apr_status_t status, apr_pool_t *p,
                                const char *fmt, ...)
                               __attribute__((format(printf,7,8)));
#endif

/**
 * ap_log_rerror() - log messages which are related to a particular
 * request.  This uses a printf-like format to log messages to the
 * error_log.
 * @param file The file in which this function is called
