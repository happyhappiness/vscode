static void mpmt_os2_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(mpmt_os2_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
}