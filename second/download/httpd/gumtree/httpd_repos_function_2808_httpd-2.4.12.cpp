static void register_hooks(apr_pool_t *p)
{
    /* Register authn provider */
    ap_register_auth_provider(p, AUTHN_PROVIDER_GROUP, "ldap",
                              AUTHN_PROVIDER_VERSION,
                              &authn_ldap_provider, AP_AUTH_INTERNAL_PER_CONF);

    /* Register authz providers */
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "ldap-user",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_ldapuser_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "ldap-group",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_ldapgroup_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "ldap-dn",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_ldapdn_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "ldap-attribute",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_ldapattribute_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "ldap-filter",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_ldapfilter_provider,
                              AP_AUTH_INTERNAL_PER_CONF);

    ap_hook_post_config(authnz_ldap_post_config,NULL,NULL,APR_HOOK_MIDDLE);

    ap_hook_optional_fn_retrieve(ImportULDAPOptFn,NULL,NULL,APR_HOOK_MIDDLE);
}