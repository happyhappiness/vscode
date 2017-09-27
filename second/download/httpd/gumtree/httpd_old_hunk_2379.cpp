#else
#define ap_log_rerror ap_log_rerror_
#endif
AP_DECLARE(void) ap_log_rerror_(const char *file, int line, int module_index,
                                int level, apr_status_t status,
                                const request_rec *r, const char *fmt, ...)
			    __attribute__((format(printf,7,8)));

/**
 * ap_log_cerror() - log messages which are related to a particular
 * connection.  This uses a printf-like format to log messages to the
 * error_log.
 * @param file The file in which this function is called
