 * @param line The line number on which this function is called
 * @param level The level of this error message
 * @param status The status code from the previous command
 * @param s The server on which we are logging
 * @param fmt The format string
 * @param ... The arguments to use to fill out fmt.
 * @note Use APLOG_MARK to fill out file and line
 * @note If a request_rec is available, use that with ap_log_rerror()
 * in preference to calling this function.  Otherwise, if a conn_rec is
 * available, use that with ap_log_cerror() in preference to calling
 * this function.
 * @warning It is VERY IMPORTANT that you not include any raw data from 
 * the network, such as the request-URI or request header fields, within 
 * the format string.  Doing so makes the server vulnerable to a 
 * denial-of-service attack and other messy behavior.  Instead, use a 
 * simple format string like "%s", followed by the string containing the 
 * untrusted data.
 */
AP_DECLARE(void) ap_log_error(const char *file, int line, int level, 
                             apr_status_t status, const server_rec *s, 
                             const char *fmt, ...)
			    __attribute__((format(printf,6,7)));

