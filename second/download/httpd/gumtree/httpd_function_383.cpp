static void register_hooks(apr_pool_t *p)
{
    ap_register_output_filter ("UPGRADE_FILTER", ssl_io_filter_Upgrade, NULL, AP_FTYPE_PROTOCOL + 5);

    ap_hook_pre_config(nwssl_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_connection(nwssl_pre_connection, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(nwssl_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_fixups(nwssl_hook_Fixup, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_http_method(nwssl_hook_http_method,   NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_default_port  (nwssl_hook_default_port,  NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_insert_filter (ssl_hook_Insert_Filter, NULL,NULL, APR_HOOK_MIDDLE);

    APR_REGISTER_OPTIONAL_FN(ssl_var_lookup);
    
    APR_REGISTER_OPTIONAL_FN(ssl_proxy_enable);
    APR_REGISTER_OPTIONAL_FN(ssl_engine_disable);
}