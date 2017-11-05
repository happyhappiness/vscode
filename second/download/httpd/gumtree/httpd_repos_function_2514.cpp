static void register_hooks(apr_pool_t *p)
{
    APR_REGISTER_OPTIONAL_FN(authn_ap_auth_type);
    APR_REGISTER_OPTIONAL_FN(authn_ap_auth_name);

    ap_hook_check_authn(authenticate_no_user, NULL, NULL, APR_HOOK_LAST,
                        AP_AUTH_INTERNAL_PER_CONF);
}