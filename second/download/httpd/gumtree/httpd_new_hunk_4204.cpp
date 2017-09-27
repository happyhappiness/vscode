 */
#ifdef DOXYGEN
AP_DECLARE(void) ap_log_rerror(const char *file, int line, int module_index,
                               int level, apr_status_t status,
                               const request_rec *r, const char *fmt, ...);
#else
#ifdef AP_HAVE_C99
/* need additional step to expand APLOG_MARK first */
#define ap_log_rerror(...) ap_log_rerror__(__VA_ARGS__)
#define ap_log_rerror__(file, line, mi, level, status, r, ...)              \
    do { if (APLOG_R_MODULE_IS_LEVEL(r, mi, level))                         \
             ap_log_rerror_(file, line, mi, level, status, r, __VA_ARGS__); \
    } while(0)
