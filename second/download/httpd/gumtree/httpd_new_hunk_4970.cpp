}

static void cgi_child_errfn(apr_pool_t *pool, apr_status_t err,
                            const char *description)
{
    apr_file_t *stderr_log;

    apr_file_open_stderr(&stderr_log, pool);
    /* Escape the logged string because it may be something that
     * came in over the network.
     */
    apr_file_printf(stderr_log,
                    "(%d)%pm: %s\n",
                    err,
                    &err,
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
                    ap_escape_logitem(pool,
#endif
                    description
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
                    )
