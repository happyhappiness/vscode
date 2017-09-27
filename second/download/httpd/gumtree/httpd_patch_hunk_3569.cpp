                                  int level, apr_status_t status,
                                  const conn_rec *c, const server_rec *s,
                                  const char *fmt, ...)
                              __attribute__((format(printf,8,9)));
 #endif
 
+/*
+ * The buffer logging functions, ap_log_data, ap_log_rdata, ap_log_cdata,
+ * and ap_log_csdata log a buffer in printable and hex format.  The exact
+ * format is controlled by processing flags, described next.
+ */
+
+/**
+ * Processing flags for ap_log_data() et al
+ *
+ * AP_LOG_DATA_DEFAULT - default formatting, with printable chars and hex
+ * AP_LOG_DATA_SHOW_OFFSET - prefix each line with hex offset from the start
+ * of the buffer
+ */
+#define AP_LOG_DATA_DEFAULT       0
+#define AP_LOG_DATA_SHOW_OFFSET   1
+
+/**
+ * ap_log_data() - log buffers which are not related to a particular request
+ * or connection.
+ * @param file The file in which this function is called
+ * @param line The line number on which this function is called
+ * @param module_index The module_index of the module logging this buffer
+ * @param level The log level
+ * @param s The server on which we are logging
+ * @param label A label for the buffer, to be logged preceding the buffer
+ * @param data The buffer to be logged
+ * @param len The length of the buffer
+ * @param flags Special processing flags like AP_LOG_DATA_SHOW_OFFSET
+ * @note ap_log_data is implemented as a macro.
+ * @note Use APLOG_MARK to fill out file, line, and module_index
+ * @note If a request_rec is available, use that with ap_log_rdata()
+ * in preference to calling this function.  Otherwise, if a conn_rec is
+ * available, use that with ap_log_cdata() in preference to calling
+ * this function.
+ */
+#ifdef DOXYGEN
+AP_DECLARE(void) ap_log_data(const char *file, int line, int module_index,
+                             int level, const server_rec *s, const char *label,
+                             const void *data, apr_size_t len, unsigned int flags);
+#else
+#ifdef AP_HAVE_C99
+/* need additional step to expand APLOG_MARK first */
+#define ap_log_data(...) ap_log_data__(__VA_ARGS__)
+/* need server_rec *sr = ... for the case if s is verbatim NULL */
+#define ap_log_data__(file, line, mi, level, s, ...)           \
+    do { const server_rec *sr__ = s; if (APLOG_MODULE_IS_LEVEL(sr__, mi, level)) \
+             ap_log_data_(file, line, mi, level, sr__, __VA_ARGS__);    \
+    } while(0)
+#else
+#define ap_log_data ap_log_data_
+#endif
+AP_DECLARE(void) ap_log_data_(const char *file, int line, int module_index,
+                              int level, const server_rec *s, const char *label,
+                              const void *data, apr_size_t len, unsigned int flags);
+#endif
+
+/**
+ * ap_log_rdata() - log buffers which are related to a particular request.
+ * @param file The file in which this function is called
+ * @param line The line number on which this function is called
+ * @param module_index The module_index of the module logging this buffer
+ * @param level The log level
+ * @param r The request which we are logging for
+ * @param label A label for the buffer, to be logged preceding the buffer
+ * @param data The buffer to be logged
+ * @param len The length of the buffer
+ * @param flags Special processing flags like AP_LOG_DATA_SHOW_OFFSET
+ * @note ap_log_rdata is implemented as a macro.
+ * @note Use APLOG_MARK to fill out file, line, and module_index
+ * @note If a request_rec is available, use that with ap_log_rerror()
+ * in preference to calling this function.  Otherwise, if a conn_rec is
+ * available, use that with ap_log_cerror() in preference to calling
+ * this function.
+ */
+#ifdef DOXYGEN
+AP_DECLARE(void) ap_log_rdata(const char *file, int line, int module_index,
+                              int level, const request_rec *r, const char *label,
+                              const void *data, apr_size_t len, unsigned int flags);
+#else
+#ifdef AP_HAVE_C99
+/* need additional step to expand APLOG_MARK first */
+#define ap_log_rdata(...) ap_log_rdata__(__VA_ARGS__)
+#define ap_log_rdata__(file, line, mi, level, s, ...)           \
+    do { if (APLOG_R_MODULE_IS_LEVEL(r, mi, level)) \
+             ap_log_rdata_(file, line, mi, level, r, __VA_ARGS__);    \
+    } while(0)
+#else
+#define ap_log_rdata ap_log_rdata_
+#endif
+AP_DECLARE(void) ap_log_rdata_(const char *file, int line, int module_index,
+                               int level, const request_rec *r, const char *label,
+                               const void *data, apr_size_t len, unsigned int flags);
+#endif
+
+/**
+ * ap_log_cdata() - log buffers which are related to a particular connection.
+ * @param file The file in which this function is called
+ * @param line The line number on which this function is called
+ * @param module_index The module_index of the module logging this buffer
+ * @param level The log level
+ * @param c The connection which we are logging for
+ * @param label A label for the buffer, to be logged preceding the buffer
+ * @param data The buffer to be logged
+ * @param len The length of the buffer
+ * @param flags Special processing flags like AP_LOG_DATA_SHOW_OFFSET
+ * @note ap_log_cdata is implemented as a macro
+ * @note Use APLOG_MARK to fill out file, line, and module_index
+ * @note If a request_rec is available, use that with ap_log_rerror()
+ * in preference to calling this function.  Otherwise, if a conn_rec is
+ * available, use that with ap_log_cerror() in preference to calling
+ * this function.
+ */
+#ifdef DOXYGEN
+AP_DECLARE(void) ap_log_cdata(const char *file, int line, int module_index,
+                              int level, const conn_rec *c, const char *label,
+                              const void *data, apr_size_t len, unsigned int flags);
+#else
+#ifdef AP_HAVE_C99
+/* need additional step to expand APLOG_MARK first */
+#define ap_log_cdata(...) ap_log_cdata__(__VA_ARGS__)
+#define ap_log_cdata__(file, line, mi, level, c, ...)           \
+    do { if (APLOG_C_MODULE_IS_LEVEL(c, mi, level)) \
+             ap_log_cdata_(file, line, mi, level, c, __VA_ARGS__);    \
+    } while(0)
+#else
+#define ap_log_cdata ap_log_cdata_
+#endif
+AP_DECLARE(void) ap_log_cdata_(const char *file, int line, int module_index,
+                               int level, const conn_rec *c, const char *label,
+                               const void *data, apr_size_t len, unsigned int flags);
+#endif
+
+/**
+ * ap_log_csdata() - log buffers which are related to a particular connection
+ * and to a vhost other than c->base_server.
+ * @param file The file in which this function is called
+ * @param line The line number on which this function is called
+ * @param module_index The module_index of the module logging this buffer
+ * @param level The log level
+ * @param c The connection which we are logging for
+ * @param s The server which we are logging for
+ * @param label A label for the buffer, to be logged preceding the buffer
+ * @param data The buffer to be logged
+ * @param len The length of the buffer
+ * @param flags Special processing flags like AP_LOG_DATA_SHOW_OFFSET
+ * @note ap_log_csdata is implemented as a macro
+ * @note Use APLOG_MARK to fill out file, line, and module_index
+ * @note If a request_rec is available, use that with ap_log_rerror()
+ * in preference to calling this function.  Otherwise, if a conn_rec is
+ * available, use that with ap_log_cerror() in preference to calling
+ * this function.
+ */
+#ifdef DOXYGEN
+AP_DECLARE(void) ap_log_csdata(const char *file, int line, int module_index,
+                               int level, const conn_rec *c, const server_rec *s,
+                               const char *label, const void *data,
+                               apr_size_t len, unsigned int flags);
+#else
+#ifdef AP_HAVE_C99
+/* need additional step to expand APLOG_MARK first */
+#define ap_log_csdata(...) ap_log_csdata__(__VA_ARGS__)
+#define ap_log_csdata__(file, line, mi, level, c, s, ...)              \
+    do { if (APLOG_CS_MODULE_IS_LEVEL(c, s, mi, level))                \
+             ap_log_csdata_(file, line, mi, level, c, s, __VA_ARGS__); \
+    } while(0)
+#else
+#define ap_log_cdata ap_log_cdata_
+#endif
+AP_DECLARE(void) ap_log_csdata_(const char *file, int line, int module_index,
+                                int level, const conn_rec *c, const server_rec *s,
+                                const char *label, const void *data,
+                                apr_size_t len, unsigned int flags);
+#endif
+
 /**
  * Convert stderr to the error log
  * @param s The current server
  */
 AP_DECLARE(void) ap_error_log2stderr(server_rec *s);
 
