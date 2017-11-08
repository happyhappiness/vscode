static int x_open_logs(apr_pool_t *pconf, apr_pool_t *plog,
                        apr_pool_t *ptemp, server_rec *s)
{
    /*
     * Log the call and exit.
     */
    trace_startup(ptemp, s, NULL, "x_open_logs()");
    return OK;
}