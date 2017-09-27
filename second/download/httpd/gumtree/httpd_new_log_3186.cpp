use that with ap_log_cerror() in preference to calling
 * this function.
 * @warning It is VERY IMPORTANT that you not include any raw data from
 * the network, such as the request-URI or request header fields, within
 * the format string.  Doing so makes the server vulnerable to a
 * denial-of-service attack and other messy behavior.  Instead, use a
 * simple format string like "%s", followed by the string containing the
 * untrusted data.
 */
#ifdef DOXYGEN
AP_DECLARE(void) ap_log_error(const char *file, int line, int module_index,
                              int level, apr_status_t status,
                              const server_rec *s, const char *fmt, ...);