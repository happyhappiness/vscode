  */
 #ifdef DOXYGEN
 AP_DECLARE(void) ap_log_perror(const char *file, int line, int module_index,
                                int level, apr_status_t status, apr_pool_t *p,
                                const char *fmt, ...);
 #else
-#if __STDC_VERSION__ >= 199901L && defined(APLOG_MAX_LOGLEVEL)
+#if defined(AP_HAVE_C99) && defined(APLOG_MAX_LOGLEVEL)
 /* need additional step to expand APLOG_MARK first */
 #define ap_log_perror(...) ap_log_perror__(__VA_ARGS__)
 #define ap_log_perror__(file, line, mi, level, status, p, ...)            \
     do { if ((level) <= APLOG_MAX_LOGLEVEL )                              \
              ap_log_perror_(file, line, mi, level, status, p,             \
                             __VA_ARGS__); } while(0)
