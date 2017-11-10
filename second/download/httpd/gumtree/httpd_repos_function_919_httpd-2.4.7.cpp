static void ssl_register_hooks(apr_pool_t *p)
{
    /* ssl_hook_ReadReq needs to use the BrowserMatch settings so must
     * run after mod_setenvif's post_read_request hook. */
    static const char *pre_prr[] = { "mod_setenvif.c", NULL };

    ssl_io_filter_register(p);

    ap_hook_pre_connection(ssl_hook_pre_connection,NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_test_config   (ssl_hook_ConfigTest,    NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config   (ssl_init_Module,        NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_http_scheme   (ssl_hook_http_scheme,   NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_default_port  (ssl_hook_default_port,  NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_pre_config    (ssl_hook_pre_config,    NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init    (ssl_init_Child,         NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_check_authn   (ssl_hook_UserCheck,     NULL,NULL, APR_HOOK_FIRST,
                           AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_fixups        (ssl_hook_Fixup,         NULL,NULL, APR_HOOK_MIDDLE);
    ap_hook_check_access  (ssl_hook_Access,        NULL,NULL, APR_HOOK_MIDDLE,
                           AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_check_authz   (ssl_hook_Auth,          NULL,NULL, APR_HOOK_MIDDLE,
                           AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_post_read_request(ssl_hook_ReadReq, pre_prr,NULL, APR_HOOK_MIDDLE);

    ssl_var_register(p);

    APR_REGISTER_OPTIONAL_FN(ssl_proxy_enable);
    APR_REGISTER_OPTIONAL_FN(ssl_engine_disable);

    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "ssl",
                              AUTHZ_PROVIDER_VERSION,
                              &ssl_authz_provider_require_ssl,
                              AP_AUTH_INTERNAL_PER_CONF);

    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "ssl-verify-client",
                              AUTHZ_PROVIDER_VERSION,
                              &ssl_authz_provider_verify_client,
                              AP_AUTH_INTERNAL_PER_CONF);

}