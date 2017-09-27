    ap_hook_pre_connection(logio_pre_conn, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_config(logio_pre_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
    ap_hook_log_transaction(logio_transaction, pre, NULL, APR_HOOK_MIDDLE);

    ap_register_input_filter(logio_filter_name, logio_in_filter, NULL,
                             AP_FTYPE_NETWORK - 1);

    APR_REGISTER_OPTIONAL_FN(ap_logio_add_bytes_out);
    APR_REGISTER_OPTIONAL_FN(ap_logio_add_bytes_in);
    APR_REGISTER_OPTIONAL_FN(ap_logio_get_last_bytes);
}

AP_DECLARE_MODULE(logio) =
{
    STANDARD20_MODULE_STUFF,
    NULL,                       /* create per-dir config */
    NULL,                       /* merge per-dir config */
    NULL,                       /* server config */
    NULL,                       /* merge server config */
