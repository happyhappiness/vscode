
static int authn_cache_precfg(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptmp)
{
    apr_status_t rv = ap_mutex_register(pconf, authn_cache_id,
                                        NULL, APR_LOCK_DEFAULT, 0);
    if (rv != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog,
                      "failed to register %s mutex", authn_cache_id);
        return 500; /* An HTTP status would be a misnomer! */
    }
    socache_provider = ap_lookup_provider(AP_SOCACHE_PROVIDER_GROUP,
                                          AP_SOCACHE_DEFAULT_PROVIDER,
                                          AP_SOCACHE_PROVIDER_VERSION);
