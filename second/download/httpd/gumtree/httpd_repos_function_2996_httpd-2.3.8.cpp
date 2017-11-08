static void simple_hooks(apr_pool_t * p)
{
    static const char *const aszSucc[] = { "core.c", NULL };

    ap_hook_open_logs(simple_open_logs, NULL, aszSucc, APR_HOOK_REALLY_FIRST);

    ap_hook_pre_config(simple_pre_config, NULL, NULL, APR_HOOK_REALLY_FIRST);

    ap_hook_check_config(simple_check_config, NULL, NULL, APR_HOOK_MIDDLE);

    ap_hook_mpm(simple_run, NULL, NULL, APR_HOOK_MIDDLE);

    ap_hook_mpm_query(simple_query, NULL, NULL, APR_HOOK_MIDDLE);

    ap_hook_mpm_get_name(simple_get_name, NULL, NULL, APR_HOOK_MIDDLE);
}