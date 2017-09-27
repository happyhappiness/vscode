        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(01675)
                      "failed to create %s mutex", authn_cache_id);
        return 500; /* An HTTP status would be a misnomer! */
    }
    apr_pool_cleanup_register(pconf, NULL, remove_lock, apr_pool_cleanup_null);

    rv = socache_provider->init(socache_instance, authn_cache_id,
                                &authn_cache_hints, s, pconf);
    if (rv != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(01677)
                      "failed to initialise %s cache", authn_cache_id);
        return 500; /* An HTTP status would be a misnomer! */
