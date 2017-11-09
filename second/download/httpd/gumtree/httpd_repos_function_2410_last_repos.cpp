static void h2_hooks(apr_pool_t *pool)
{
    static const char *const mod_ssl[] = { "mod_ssl.c", NULL};
    
    APR_REGISTER_OPTIONAL_FN(http2_is_h2);
    APR_REGISTER_OPTIONAL_FN(http2_var_lookup);
    APR_REGISTER_OPTIONAL_FN(http2_req_engine_push);
    APR_REGISTER_OPTIONAL_FN(http2_req_engine_pull);
    APR_REGISTER_OPTIONAL_FN(http2_req_engine_done);

    ap_log_perror(APLOG_MARK, APLOG_TRACE1, 0, pool, "installing hooks");
    
    /* Run once after configuration is set, but before mpm children initialize.
     */
    ap_hook_post_config(h2_post_config, mod_ssl, NULL, APR_HOOK_MIDDLE);
    
    /* Run once after a child process has been created.
     */
    ap_hook_child_init(h2_child_init, NULL, NULL, APR_HOOK_MIDDLE);

    h2_h2_register_hooks();
    h2_switch_register_hooks();
    h2_task_register_hooks();

    h2_alt_svc_register_hooks();
    
    /* Setup subprocess env for certain variables 
     */
    ap_hook_fixups(h2_h2_fixups, NULL,NULL, APR_HOOK_MIDDLE);
    
    /* test http2 connection status handler */
    ap_hook_handler(h2_filter_h2_status_handler, NULL, NULL, APR_HOOK_MIDDLE);
}