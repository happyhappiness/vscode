static void rewrite_child_errfn(apr_pool_t *p, apr_status_t err,
                                const char *desc)
{
    ap_log_error(APLOG_MARK, APLOG_ERR, err, NULL, "%s", desc);
}