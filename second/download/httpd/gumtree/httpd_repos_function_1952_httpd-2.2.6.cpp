static void authn_dbd_hooks(apr_pool_t *p)
{
    static const authn_provider authn_dbd_provider = {
        &authn_dbd_password,
        &authn_dbd_realm
    };

    ap_register_provider(p, AUTHN_PROVIDER_GROUP, "dbd", "0", &authn_dbd_provider);
}