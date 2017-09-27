#define APLOGctrace4(c)             APLOG_C_IS_LEVEL(c,APLOG_TRACE4)
#define APLOGctrace5(c)             APLOG_C_IS_LEVEL(c,APLOG_TRACE5)
#define APLOGctrace6(c)             APLOG_C_IS_LEVEL(c,APLOG_TRACE6)
#define APLOGctrace7(c)             APLOG_C_IS_LEVEL(c,APLOG_TRACE7)
#define APLOGctrace8(c)             APLOG_C_IS_LEVEL(c,APLOG_TRACE8)

extern int AP_DECLARE_DATA ap_default_loglevel;

/**
 * APLOG_MARK is a convenience macro for use as the first three parameters in
 * ap_log_error() and related functions, i.e. file, line, and module_index.
 *
 * The module_index parameter was introduced in version 2.3.6. Before that
