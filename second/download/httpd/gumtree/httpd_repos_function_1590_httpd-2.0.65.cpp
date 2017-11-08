static void mod_auth_ldap_register_hooks(apr_pool_t *p)
{
    ap_hook_post_config(auth_ldap_post_config,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_check_user_id(mod_auth_ldap_check_user_id, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_auth_checker(mod_auth_ldap_auth_checker, NULL, NULL, APR_HOOK_MIDDLE);
}