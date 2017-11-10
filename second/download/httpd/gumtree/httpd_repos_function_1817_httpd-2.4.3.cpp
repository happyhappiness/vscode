static int proxy_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                            apr_pool_t *ptemp)
{
    APR_OPTIONAL_HOOK(ap, status_hook, proxy_status_hook, NULL, NULL,
                      APR_HOOK_MIDDLE);
    /* Reset workers count on gracefull restart */
    proxy_lb_workers = 0;
    return OK;
}