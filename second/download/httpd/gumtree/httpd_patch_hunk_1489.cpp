 /**
  * ap_log_error() - log messages which are not related to a particular
  * request or connection.  This uses a printf-like format to log messages
  * to the error_log.
  * @param file The file in which this function is called
  * @param line The line number on which this function is called
+ * @param module_index The module_index of the module generating this message
  * @param level The level of this error message
  * @param status The status code from the previous command
  * @param s The server on which we are logging
  * @param fmt The format string
  * @param ... The arguments to use to fill out fmt.
  * @note Use APLOG_MARK to fill out file and line
