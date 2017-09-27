                                 int level, apr_status_t status, apr_pool_t *p,
                                 const char *fmt, ...)
                                __attribute__((format(printf,7,8)));
 
 /**
  * ap_log_rerror() - log messages which are related to a particular
- * request.  This uses a a printf-like format to log messages to the
+ * request.  This uses a printf-like format to log messages to the
  * error_log.
  * @param file The file in which this function is called
  * @param line The line number on which this function is called
  * @param module_index The module_index of the module generating this message
  * @param level The level of this error message
  * @param status The status code from the previous command
