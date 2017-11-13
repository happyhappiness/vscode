static void log_child_errfn(apr_pool_t *pool, apr_status_t err,
                            const char *description)
{
    ap_log_error(APLOG_MARK, APLOG_ERR, err, NULL,
                 "%s", description);
}