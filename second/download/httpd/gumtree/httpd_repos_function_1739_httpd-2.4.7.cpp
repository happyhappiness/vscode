static int cgid_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                           apr_pool_t *ptemp)
{
    sockname = ap_append_pid(pconf, DEFAULT_SOCKET, ".");
    return OK;
}