 * untrusted data.
 */
#if __STDC_VERSION__ >= 199901L
/* need additional step to expand APLOG_MARK first */
#define ap_log_cerror(...) ap_log_cerror__(__VA_ARGS__)
#define ap_log_cerror__(file, line, mi, level, status, c, ...)              \
    do { if (APLOG_MODULE_IS_LEVEL(c->base_server, mi, level))              \
             ap_log_cerror_(file, line, mi, level, status, c, __VA_ARGS__); \
    } while(0)
#else
#define ap_log_cerror ap_log_cerror_
#endif
AP_DECLARE(void) ap_log_cerror_(const char *file, int line, int module_level,
                                int level, apr_status_t status,
                                const conn_rec *c, const char *fmt, ...)
			    __attribute__((format(printf,7,8)));

/**
 * Convert stderr to the error log
 * @param s The current server
 */
AP_DECLARE(void) ap_error_log2stderr(server_rec *s);

/**
