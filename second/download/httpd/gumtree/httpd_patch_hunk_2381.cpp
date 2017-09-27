  * @param module_index The module_index of the module generating this message
  * @param status The status code from the previous command
  * @param c The connection which we are logging for
  * @param s The server which we are logging for
  * @param fmt The format string
  * @param ... The arguments to use to fill out fmt.
- * @note Use APLOG_MARK to fill out file and line
+ * @note ap_log_cserror is implemented as a macro
+ * @note Use APLOG_MARK to fill out file, line, and module_index
  * @note If a request_rec is available, use that with ap_log_rerror()
  * in preference to calling this function. This function is mainly useful for
  * modules like mod_ssl to use before the request_rec is created.
- * @warning It is VERY IMPORTANT that you not include any raw data from 
- * the network, such as the request-URI or request header fields, within 
- * the format string.  Doing so makes the server vulnerable to a 
- * denial-of-service attack and other messy behavior.  Instead, use a 
- * simple format string like "%s", followed by the string containing the 
+ * @warning It is VERY IMPORTANT that you not include any raw data from
+ * the network, such as the request-URI or request header fields, within
+ * the format string.  Doing so makes the server vulnerable to a
+ * denial-of-service attack and other messy behavior.  Instead, use a
+ * simple format string like "%s", followed by the string containing the
  * untrusted data.
  */
+#ifdef DOXYGEN
+AP_DECLARE(void) ap_log_cserror(const char *file, int line, int module_index,
+                                int level, apr_status_t status,
+                                const conn_rec *c, const server_rec *s,
+                                const char *fmt, ...);
+#else
 #if __STDC_VERSION__ >= 199901L
 /* need additional step to expand APLOG_MARK first */
 #define ap_log_cserror(...) ap_log_cserror__(__VA_ARGS__)
 #define ap_log_cserror__(file, line, mi, level, status, c, s, ...)  \
     do { if (APLOG_CS_MODULE_IS_LEVEL(c, s, mi, level))             \
              ap_log_cserror_(file, line, mi, level, status, c, s,   \
                              __VA_ARGS__);                          \
     } while(0)
 #else
 #define ap_log_cserror ap_log_cserror_
 #endif
-AP_DECLARE(void) ap_log_cserror_(const char *file, int line, int module_level,
+AP_DECLARE(void) ap_log_cserror_(const char *file, int line, int module_index,
                                  int level, apr_status_t status,
                                  const conn_rec *c, const server_rec *s,
                                  const char *fmt, ...)
                              __attribute__((format(printf,8,9)));
+#endif
 
 /**
  * Convert stderr to the error log
  * @param s The current server
  */
 AP_DECLARE(void) ap_error_log2stderr(server_rec *s);
