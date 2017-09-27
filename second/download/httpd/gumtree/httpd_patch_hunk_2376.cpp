  * @param module_index ignored dummy value for use by APLOG_MARK
  * @param level The level of this error message
  * @param status The status code from the previous command
  * @param p The pool which we are logging for
  * @param fmt The format string
  * @param ... The arguments to use to fill out fmt.
- * @note Use APLOG_MARK to fill out file and line
- * @warning It is VERY IMPORTANT that you not include any raw data from 
- * the network, such as the request-URI or request header fields, within 
- * the format string.  Doing so makes the server vulnerable to a 
- * denial-of-service attack and other messy behavior.  Instead, use a 
- * simple format string like "%s", followed by the string containing the 
+ * @note ap_log_perror is implemented as a macro
+ * @note Use APLOG_MARK to fill out file, line, and module_index
+ * @warning It is VERY IMPORTANT that you not include any raw data from
+ * the network, such as the request-URI or request header fields, within
+ * the format string.  Doing so makes the server vulnerable to a
+ * denial-of-service attack and other messy behavior.  Instead, use a
+ * simple format string like "%s", followed by the string containing the
  * untrusted data.
  */
+#ifdef DOXYGEN
+AP_DECLARE(void) ap_log_perror(const char *file, int line, int module_index,
+                               int level, apr_status_t status, apr_pool_t *p,
+                               const char *fmt, ...);
+#else
 #if __STDC_VERSION__ >= 199901L && defined(APLOG_MAX_LOGLEVEL)
 /* need additional step to expand APLOG_MARK first */
 #define ap_log_perror(...) ap_log_perror__(__VA_ARGS__)
 #define ap_log_perror__(file, line, mi, level, status, p, ...)            \
     do { if ((level) <= APLOG_MAX_LOGLEVEL )                              \
              ap_log_perror_(file, line, mi, level, status, p,             \
