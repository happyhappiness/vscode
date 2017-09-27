  * @param module_index The module_index of the module generating this message
  * @param level The level of this error message
  * @param status The status code from the previous command
  * @param r The request which we are logging for
  * @param fmt The format string
  * @param ... The arguments to use to fill out fmt.
- * @note Use APLOG_MARK to fill out file and line
- * @warning It is VERY IMPORTANT that you not include any raw data from 
- * the network, such as the request-URI or request header fields, within 
- * the format string.  Doing so makes the server vulnerable to a 
- * denial-of-service attack and other messy behavior.  Instead, use a 
- * simple format string like "%s", followed by the string containing the 
+ * @note ap_log_rerror is implemented as a macro
+ * @note Use APLOG_MARK to fill out file, line, and module_index
+ * @warning It is VERY IMPORTANT that you not include any raw data from
+ * the network, such as the request-URI or request header fields, within
+ * the format string.  Doing so makes the server vulnerable to a
+ * denial-of-service attack and other messy behavior.  Instead, use a
+ * simple format string like "%s", followed by the string containing the
  * untrusted data.
  */
+#ifdef DOXYGEN
+AP_DECLARE(void) ap_log_rerror(const char *file, int line, int module_index,
+                               int level, apr_status_t status,
+                               const request_rec *r, const char *fmt, ...);
+#else
 #if __STDC_VERSION__ >= 199901L
 /* need additional step to expand APLOG_MARK first */
 #define ap_log_rerror(...) ap_log_rerror__(__VA_ARGS__)
 #define ap_log_rerror__(file, line, mi, level, status, r, ...)              \
     do { if (APLOG_R_MODULE_IS_LEVEL(r, mi, level))                         \
              ap_log_rerror_(file, line, mi, level, status, r, __VA_ARGS__); \
