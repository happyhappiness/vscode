static void
dialup_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(dialup_handler, NULL, NULL, APR_HOOK_ALMOST_LAST);
}