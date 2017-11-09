static void hc_register_hooks(apr_pool_t *p)
{
    static const char *const aszPre[] = { "mod_proxy_balancer.c", "mod_proxy.c", NULL};
    static const char *const aszSucc[] = { "mod_watchdog.c", NULL};
    APR_REGISTER_OPTIONAL_FN(set_worker_hc_param);
    APR_REGISTER_OPTIONAL_FN(hc_show_exprs);
    APR_REGISTER_OPTIONAL_FN(hc_select_exprs);
    APR_REGISTER_OPTIONAL_FN(hc_valid_expr);
    ap_hook_pre_config(hc_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(hc_post_config, aszPre, aszSucc, APR_HOOK_LAST);
    ap_hook_expr_lookup(hc_expr_lookup, NULL, NULL, APR_HOOK_MIDDLE);
}