static void register_hooks(apr_pool_t *p)
{
    ap_register_provider(p, AP_SOCACHE_PROVIDER_GROUP, "shmcb",
                         AP_SOCACHE_PROVIDER_VERSION,
                         &socache_shmcb);

    /* Also register shmcb under the default provider name. */
    ap_register_provider(p, AP_SOCACHE_PROVIDER_GROUP,
                         AP_SOCACHE_DEFAULT_PROVIDER,
                         AP_SOCACHE_PROVIDER_VERSION,
                         &socache_shmcb);
}