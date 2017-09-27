 */
#ifdef DOXYGEN
AP_DECLARE(void) ap_log_error(const char *file, int line, int module_index,
                              int level, apr_status_t status,
                              const server_rec *s, const char *fmt, ...);
#else
#if __STDC_VERSION__ >= 199901L
/* need additional step to expand APLOG_MARK first */
#define ap_log_error(...) ap_log_error__(__VA_ARGS__)
/* need server_rec *sr = ... for the case if s is verbatim NULL */
#define ap_log_error__(file, line, mi, level, status, s, ...)           \
    do { const server_rec *sr = s; if (APLOG_MODULE_IS_LEVEL(sr, mi, level))      \
             ap_log_error_(file, line, mi, level, status, sr, __VA_ARGS__); \
