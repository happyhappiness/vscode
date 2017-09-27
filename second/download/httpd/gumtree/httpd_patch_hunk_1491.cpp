  * the network, such as the request-URI or request header fields, within 
  * the format string.  Doing so makes the server vulnerable to a 
  * denial-of-service attack and other messy behavior.  Instead, use a 
  * simple format string like "%s", followed by the string containing the 
  * untrusted data.
  */
-AP_DECLARE(void) ap_log_perror(const char *file, int line, int level, 
-                             apr_status_t status, apr_pool_t *p, 
-                             const char *fmt, ...)
-			    __attribute__((format(printf,6,7)));
+#if __STDC_VERSION__ >= 199901L && defined(APLOG_MAX_LOGLEVEL)
+/* need additional step to expand APLOG_MARK first */
+#define ap_log_perror(...) ap_log_perror__(__VA_ARGS__)
+#define ap_log_perror__(file, line, mi, level, status, p, ...)            \
+    do { if ((level) <= APLOG_MAX_LOGLEVEL )                              \
+             ap_log_perror_(file, line, mi, level, status, p,             \
+                            __VA_ARGS__); } while(0)
+#else
+#define ap_log_perror ap_log_perror_
+#endif
+AP_DECLARE(void) ap_log_perror_(const char *file, int line, int module_index,
+                                int level, apr_status_t status, apr_pool_t *p,
+                                const char *fmt, ...)
+                               __attribute__((format(printf,7,8)));
 
 /**
  * ap_log_rerror() - log messages which are related to a particular
  * request.  This uses a a printf-like format to log messages to the
  * error_log.
  * @param file The file in which this function is called
  * @param line The line number on which this function is called
+ * @param module_index The module_index of the module generating this message
  * @param level The level of this error message
  * @param status The status code from the previous command
  * @param r The request which we are logging for
  * @param fmt The format string
  * @param ... The arguments to use to fill out fmt.
  * @note Use APLOG_MARK to fill out file and line
