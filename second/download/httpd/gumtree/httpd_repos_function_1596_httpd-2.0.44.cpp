static void util_ldap_register_hooks(apr_pool_t *p)
{
    ap_hook_child_init(util_ldap_init_module, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(util_ldap_handler, NULL, NULL, APR_HOOK_MIDDLE);
}