static void socache_status_register(apr_pool_t *p)
{
    APR_OPTIONAL_HOOK(ap, status_hook, socache_status_hook, NULL, NULL, APR_HOOK_MIDDLE);
}