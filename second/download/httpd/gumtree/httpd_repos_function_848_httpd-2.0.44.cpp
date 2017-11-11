static void ssl_register_hooks(apr_pool_t *p)
{
    ssl_io_filter_register(p);

    ap_hook_pre_connection(ssl_hook_pre_connection,NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config   (ssl_init_Module,        NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_http_method   (ssl_hook_http_method,   NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_default_port  (ssl_hook_default_port,  NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_config    (ssl_hook_pre_config,    NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init    (ssl_init_Child,         NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_translate_name(ssl_hook_Translate,     NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_check_user_id (ssl_hook_UserCheck,     NULL,NULL, APR_HOOK_FIRST);
    ap_hook_fixups        (ssl_hook_Fixup,         NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_access_checker(ssl_hook_Access,        NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_auth_checker  (ssl_hook_Auth,          NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_post_read_request(ssl_hook_ReadReq,    NULL,NULL, APR_HOOK_MIDDLE);

    ssl_var_register();

    APR_REGISTER_OPTIONAL_FN(ssl_proxy_enable);
    APR_REGISTER_OPTIONAL_FN(ssl_engine_disable);
}