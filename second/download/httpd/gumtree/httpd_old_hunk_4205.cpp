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
