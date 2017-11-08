static void register_hooks(apr_pool_t *p)
{
    ap_register_provider(p, AUTHN_PROVIDER_GROUP, "anon", "0",
                         &authn_anon_provider);
}