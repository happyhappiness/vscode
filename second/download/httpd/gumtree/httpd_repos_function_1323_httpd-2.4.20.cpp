static void register_hooks(apr_pool_t *p)
{
#ifdef HAVE_APU_MEMCACHE
    ap_register_provider(p, AP_SOCACHE_PROVIDER_GROUP, "memcache",
                         AP_SOCACHE_PROVIDER_VERSION,
                         &socache_mc);
#endif
}