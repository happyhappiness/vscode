static void register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(authz_some_auth_required);

    ap_hook_pre_config(authz_core_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_check_config(authz_core_check_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_check_authz(authorize_user, NULL, NULL, APR_HOOK_LAST,
                        AP_AUTH_INTERNAL_PER_CONF);
}