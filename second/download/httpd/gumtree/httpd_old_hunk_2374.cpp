
/**
 * Replace logging to stderr with logging to the given file.
 * @param p The pool to allocate out of
 * @param file Name of the file to log stderr output
 */
AP_DECLARE(apr_status_t) ap_replace_stderr_log(apr_pool_t *p, 
                                               const char *file);

/**
 * Open the error log and replace stderr with it.
 * @param pconf Not used
 * @param plog  The pool to allocate the logs from
 * @param ptemp Pool used for temporary allocations
 * @param s_main The main server
 * @note ap_open_logs isn't expected to be used by modules, it is
 * an internal core function 
 */
int ap_open_logs(apr_pool_t *pconf, apr_pool_t *plog, 
                 apr_pool_t *ptemp, server_rec *s_main);

/**
 * Perform special processing for piped loggers in MPM child
 * processes.
 * @param p Not used
 * @param s Not used
 * @note ap_logs_child_init is not for use by modules; it is an
 * internal core function
 */
void ap_logs_child_init(apr_pool_t *p, server_rec *s);

/* 
 * The primary logging functions, ap_log_error, ap_log_rerror, ap_log_cerror,
 * and ap_log_perror use a printf style format string to build the log message.  
 * It is VERY IMPORTANT that you not include any raw data from the network, 
 * such as the request-URI or request header fields, within the format 
 * string.  Doing so makes the server vulnerable to a denial-of-service 
 * attack and other messy behavior.  Instead, use a simple format string 
 * like "%s", followed by the string containing the untrusted data.
 */

/**
 * ap_log_error() - log messages which are not related to a particular
 * request or connection.  This uses a printf-like format to log messages
