 #else
 #ifdef AP_HAVE_C99
 /* need additional step to expand APLOG_MARK first */
 #define ap_log_error(...) ap_log_error__(__VA_ARGS__)
 /* need server_rec *sr = ... for the case if s is verbatim NULL */
 #define ap_log_error__(file, line, mi, level, status, s, ...)           \
-    do { const server_rec *sr = s; if (APLOG_MODULE_IS_LEVEL(sr, mi, level))      \
-             ap_log_error_(file, line, mi, level, status, sr, __VA_ARGS__); \
+    do { const server_rec *sr__ = s; if (APLOG_MODULE_IS_LEVEL(sr__, mi, level)) \
+             ap_log_error_(file, line, mi, level, status, sr__, __VA_ARGS__);    \
     } while(0)
 #else
 #define ap_log_error ap_log_error_
 #endif
 AP_DECLARE(void) ap_log_error_(const char *file, int line, int module_index,
                                int level, apr_status_t status,
