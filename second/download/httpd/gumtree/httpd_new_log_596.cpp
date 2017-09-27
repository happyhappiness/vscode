use that with ap_log_rerror()
 * in preference to calling this function.
 * @warning It is VERY IMPORTANT that you not include any raw data from 
 * the network, such as the request-URI or request header fields, within 
 * the format string.  Doing so makes the server vulnerable to a 
 * denial-of-service attack and other messy behavior.  Instead, use a 
 * simple format string like "%s", followed by the string containing the 
 * untrusted data.
 */
AP_DECLARE(void) ap_log_cerror(const char *file, int line, int level, 
                               apr_status_t status, const conn_rec *c, 
                               const char *fmt, ...)
			    __attribute__((format(printf,6,7)));