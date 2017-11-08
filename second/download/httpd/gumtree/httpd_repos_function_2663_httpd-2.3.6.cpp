static void authn_dbd_hooks(apr_pool_t *p)
{
    static const authn_provider authn_dbd_provider = {
        &authn_dbd_password,
        &authn_dbd_realm
    };

    ap_register_auth_provider(p, AUTHN_PROVIDER_GROUP, "dbd",
                              AUTHN_PROVIDER_VERSION,
                              &authn_dbd_provider, AP_AUTH_INTERNAL_PER_CONF);
}