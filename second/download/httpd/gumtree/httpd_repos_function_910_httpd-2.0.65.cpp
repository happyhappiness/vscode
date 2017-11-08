static void register_hooks(apr_pool_t *p)
{
    ap_hook_fixups(check_speling,NULL,NULL,APR_HOOK_LAST);
}