static void mpmt_os2_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(mpmt_os2_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_check_config(mpmt_os2_check_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_mpm(mpmt_os2_run, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_mpm_query(mpmt_os2_query, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_mpm_get_name(mpmt_os2_get_name, NULL, NULL, APR_HOOK_MIDDLE);
}