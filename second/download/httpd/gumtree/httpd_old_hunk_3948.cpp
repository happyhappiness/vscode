
#define CFG_CHECK(x) if ((x) == -1) { \
    char msgbuf[128]; \
    apr_strerror(errno, msgbuf, sizeof(msgbuf)); \
    return apr_pstrdup(cmd->pool, msgbuf); \
}
#define CR_CHECK(x) if (x == -1) \
    ap_log_error(APLOG_MARK, APLOG_CRIT, errno, 0, \
                 "Failed to initialise privileges")

module AP_MODULE_DECLARE_DATA privileges_module;

/* #define BIG_SECURITY_HOLE 1 */

