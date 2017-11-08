static void register_hooks(apr_pool_t *p)
{
    ap_register_provider(p, AP_SOCACHE_PROVIDER_GROUP, "dbm", 
                         AP_SOCACHE_PROVIDER_VERSION,
                         &socache_dbm);
}