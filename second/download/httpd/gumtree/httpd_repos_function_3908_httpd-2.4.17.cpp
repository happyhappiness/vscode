static void netware_mpm_hooks(apr_pool_t *p)
{
    /* Run the pre-config hook after core's so that it can override the
     * default setting of ThreadStackSize for NetWare.
     */
    static const char * const predecessors[] = {"core.c", NULL};

    ap_hook_pre_config(netware_pre_config, predecessors, NULL, APR_HOOK_MIDDLE);
    ap_hook_check_config(netware_check_config, NULL, NULL, APR_HOOK_MIDDLE);
    //ap_hook_post_config(netware_post_config, NULL, NULL, 0);
    //ap_hook_child_init(netware_child_init, NULL, NULL, APR_HOOK_MIDDLE);
    //ap_hook_open_logs(netware_open_logs, NULL, aszSucc, APR_HOOK_REALLY_FIRST);
    ap_hook_mpm(netware_run, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_mpm_query(netware_query, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_mpm_get_name(netware_get_name, NULL, NULL, APR_HOOK_MIDDLE);
}