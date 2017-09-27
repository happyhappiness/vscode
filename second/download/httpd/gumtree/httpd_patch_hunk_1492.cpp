  * the network, such as the request-URI or request header fields, within 
  * the format string.  Doing so makes the server vulnerable to a 
  * denial-of-service attack and other messy behavior.  Instead, use a 
  * simple format string like "%s", followed by the string containing the 
  * untrusted data.
  */
-AP_DECLARE(void) ap_log_rerror(const char *file, int line, int level, 
-                               apr_status_t status, const request_rec *r, 
-                               const char *fmt, ...)
-			    __attribute__((format(printf,6,7)));
+#if __STDC_VERSION__ >= 199901L
+/* need additional step to expand APLOG_MARK first */
+#define ap_log_rerror(...) ap_log_rerror__(__VA_ARGS__)
+#define ap_log_rerror__(file, line, mi, level, status, r, ...)              \
+    do { if (APLOG_MODULE_IS_LEVEL(r->server, mi, level))                   \
+             ap_log_rerror_(file, line, mi, level, status, r, __VA_ARGS__); \
+    } while(0)
+#else
+#define ap_log_rerror ap_log_rerror_
+#endif
+AP_DECLARE(void) ap_log_rerror_(const char *file, int line, int module_index,
+                                int level, apr_status_t status,
+                                const request_rec *r, const char *fmt, ...)
+			    __attribute__((format(printf,7,8)));
 
 /**
  * ap_log_cerror() - log messages which are related to a particular
  * connection.  This uses a a printf-like format to log messages to the
  * error_log.
  * @param file The file in which this function is called
  * @param line The line number on which this function is called
  * @param level The level of this error message
+ * @param module_index The module_index of the module generating this message
  * @param status The status code from the previous command
  * @param c The connection which we are logging for
  * @param fmt The format string
  * @param ... The arguments to use to fill out fmt.
  * @note Use APLOG_MARK to fill out file and line
  * @note If a request_rec is available, use that with ap_log_rerror()
