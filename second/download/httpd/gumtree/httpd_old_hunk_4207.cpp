    ap_log_set_writer(ap_default_log_writer);
    buffered_logs = 0;

    return OK;
}

static void register_hooks(apr_pool_t *p)
{
    ap_hook_pre_config(log_pre_config,NULL,NULL,APR_HOOK_REALLY_FIRST);
    ap_hook_child_init(init_child,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_open_logs(init_config_log,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_log_transaction(multi_log_transaction,NULL,NULL,APR_HOOK_MIDDLE);

    /* Init log_hash before we register the optional function. It is
     * possible for the optional function, ap_register_log_handler,
