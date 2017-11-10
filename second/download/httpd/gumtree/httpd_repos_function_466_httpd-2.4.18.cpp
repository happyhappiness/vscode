static void register_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(log_pre_config,NULL,NULL,APR_HOOK_REALLY_FIRST);
    ap_hook_check_config(log_check_config,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_child_init(init_child,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_open_logs(init_config_log,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_log_transaction(multi_log_transaction,NULL,NULL,APR_HOOK_MIDDLE);

    /* Init log_hash before we register the optional function. It is
     * possible for the optional function, ap_register_log_handler,
     * to be called before any other mod_log_config hooks are called.
     * As a policy, we should init everything required by an optional function
     * before calling APR_REGISTER_OPTIONAL_FN.
     */
    log_hash = apr_hash_make(p);
    APR_REGISTER_OPTIONAL_FN(ap_register_log_handler);
    APR_REGISTER_OPTIONAL_FN(ap_log_set_writer_init);
    APR_REGISTER_OPTIONAL_FN(ap_log_set_writer);
}