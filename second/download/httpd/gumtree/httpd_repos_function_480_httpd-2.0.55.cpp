static void register_hooks(apr_pool_t *p)
{
    ap_hook_fixups(spot_cookie,NULL,NULL,APR_HOOK_MIDDLE);
}