static void register_hooks(apr_pool_t *p)
{
    ap_hook_handler(asis_handler,NULL,NULL,APR_HOOK_MIDDLE);
}