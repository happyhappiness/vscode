 * @tip ap_open_logs isn't expected to be used by modules, it is
 * an internal core function 
 */
int ap_open_logs(apr_pool_t *pconf, apr_pool_t *plog, 
                 apr_pool_t *ptemp, server_rec *s_main);

/* 
 * The three primary logging functions, ap_log_error, ap_log_rerror, and 
 * ap_log_perror use a printf style format string to build the log message.  
 * It is VERY IMPORTANT that you not include any raw data from the network, 
 * such as the request-URI or request header fields, within the format 
 * string.  Doing so makes the server vulnerable to a denial-of-service 
 * attack and other messy behavior.  Instead, use a simple format string 
 * like "%s", followed by the string containing the untrusted data.
 */

/**
 * One of the primary logging routines in Apache.  This uses a printf-like
 * format to log messages to the error_log.
 * @param file The file in which this function is called
 * @param line The line number on which this function is called
 * @param level The level of this error message
 * @param status The status code from the previous command
 * @param s The server on which we are logging
 * @param fmt The format string
 * @param ... The arguments to use to fill out fmt.
 * @tip Use APLOG_MARK to fill out file and line
 * @warning It is VERY IMPORTANT that you not include any raw data from 
 * the network, such as the request-URI or request header fields, within 
 * the format string.  Doing so makes the server vulnerable to a 
 * denial-of-service attack and other messy behavior.  Instead, use a 
 * simple format string like "%s", followed by the string containing the 
 * untrusted data.
