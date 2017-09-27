#define APLOGctrace6(c)             APLOG_C_IS_LEVEL(c,APLOG_TRACE6)
#define APLOGctrace7(c)             APLOG_C_IS_LEVEL(c,APLOG_TRACE7)
#define APLOGctrace8(c)             APLOG_C_IS_LEVEL(c,APLOG_TRACE8)

extern int AP_DECLARE_DATA ap_default_loglevel;

/**
 * APLOG_MARK is a convenience macro for use as the first three parameters in
 * ap_log_error() and related functions, i.e. file, line, and module_index.
 *
 * The module_index parameter was introduced in version 2.3.6. Before that
 * version, APLOG_MARK only replaced the file and line parameters.
 * This means that APLOG_MARK can be used with ap_log_*error in all versions
 * of Apache httpd.
 *
 * @see APLOG_MODULE_INDEX
 * @see ap_log_error
 * @see ap_log_cerror
 * @see ap_log_rerror
 * @see ap_log_cserror
 */
#define APLOG_MARK     __FILE__,__LINE__,APLOG_MODULE_INDEX

/**
 * Set up for logging to stderr.
 * @param p The pool to allocate out of
 */
