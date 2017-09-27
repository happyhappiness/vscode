#define APLOGctrace6(c)             APLOG_C_IS_LEVEL(c,APLOG_TRACE6)
#define APLOGctrace7(c)             APLOG_C_IS_LEVEL(c,APLOG_TRACE7)
#define APLOGctrace8(c)             APLOG_C_IS_LEVEL(c,APLOG_TRACE8)

extern int AP_DECLARE_DATA ap_default_loglevel;

#define APLOG_MARK     __FILE__,__LINE__,APLOG_MODULE_INDEX

/**
 * Set up for logging to stderr.
 * @param p The pool to allocate out of
 */
