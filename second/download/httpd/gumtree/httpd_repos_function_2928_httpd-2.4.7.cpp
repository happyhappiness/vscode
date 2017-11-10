static void register_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHN_PROVIDER_GROUP, "dbm",
                              AUTHN_PROVIDER_VERSION,
                              &authn_dbm_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_hook_optional_fn_retrieve(opt_retr, NULL, NULL, APR_HOOK_MIDDLE);
}