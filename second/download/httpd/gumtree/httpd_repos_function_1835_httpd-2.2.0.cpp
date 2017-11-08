static void register_hooks(apr_pool_t *p)
{
    static const char * const aszPost[]={ "mod_authz_user.c", NULL };

    ap_register_provider(p, AUTHN_PROVIDER_GROUP, "ldap", "0",
                         &authn_ldap_provider);
    ap_hook_post_config(authnz_ldap_post_config,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_auth_checker(authz_ldap_check_user_access, NULL, aszPost, APR_HOOK_MIDDLE);

    ap_hook_optional_fn_retrieve(ImportULDAPOptFn,NULL,NULL,APR_HOOK_MIDDLE);
}