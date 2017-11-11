static int x_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                          apr_pool_t *ptemp, server_rec *s)
{
    /*
     * Log the call and exit.
     */
    trace_startup(ptemp, s, NULL, "x_post_config()");
    return OK;
}