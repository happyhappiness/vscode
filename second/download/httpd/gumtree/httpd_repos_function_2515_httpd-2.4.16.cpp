static int x_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                        apr_pool_t *ptemp)
{
    /*
     * Log the call and exit.
     */
    trace_startup(ptemp, NULL, NULL, "x_pre_config()");
    return OK;
}