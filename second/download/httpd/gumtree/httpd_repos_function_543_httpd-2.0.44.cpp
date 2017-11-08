static void register_hooks(apr_pool_t *p)
{
    ap_hook_fixups(add_expires,NULL,NULL,APR_HOOK_MIDDLE);
}