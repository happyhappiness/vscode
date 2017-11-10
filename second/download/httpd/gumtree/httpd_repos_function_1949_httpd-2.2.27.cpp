static void util_ldap_register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(uldap_connection_open);
    APR_REGISTER_OPTIONAL_FN(uldap_connection_close);
    APR_REGISTER_OPTIONAL_FN(uldap_connection_unbind);
    APR_REGISTER_OPTIONAL_FN(uldap_connection_cleanup);
    APR_REGISTER_OPTIONAL_FN(uldap_connection_find);
    APR_REGISTER_OPTIONAL_FN(uldap_cache_comparedn);
    APR_REGISTER_OPTIONAL_FN(uldap_cache_compare);
    APR_REGISTER_OPTIONAL_FN(uldap_cache_checkuserid);
    APR_REGISTER_OPTIONAL_FN(uldap_cache_getuserdn);
    APR_REGISTER_OPTIONAL_FN(uldap_ssl_supported);

    ap_hook_post_config(util_ldap_post_config,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_handler(util_ldap_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(util_ldap_child_init, NULL, NULL, APR_HOOK_MIDDLE);
}