static void register_hooks(apr_pool_t *p)
{
    static const char *pre[] = { "mod_log_config.c", NULL };

    ap_hook_pre_connection(logio_pre_conn, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_config(logio_pre_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
    ap_hook_log_transaction(logio_transaction, pre, NULL, APR_HOOK_MIDDLE);

    ap_register_input_filter(logio_filter_name, logio_in_filter, NULL,
                             AP_FTYPE_NETWORK - 1);
    ap_register_output_filter(logio_filter_name, logio_out_filter, NULL,
                              AP_FTYPE_NETWORK - 1);

    APR_REGISTER_OPTIONAL_FN(ap_logio_add_bytes_out);
    APR_REGISTER_OPTIONAL_FN(ap_logio_add_bytes_in);
}