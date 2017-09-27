    static struct ap_socache_hints authn_cache_hints = {64, 32, 60000000};

    if (!configured) {
        return OK;    /* don't waste the overhead of creating mutex & cache */
    }
    if (socache_provider == NULL) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, plog,
                      "Please select a socache provider with AuthnCacheSOCache "
                      "(no default found on this platform)");
        return 500; /* An HTTP status would be a misnomer! */
    }

    rv = ap_global_mutex_create(&authn_cache_mutex, NULL,
                                authn_cache_id, NULL, s, pconf, 0);
    if (rv != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog,
                      "failed to create %s mutex", authn_cache_id);
        return 500; /* An HTTP status would be a misnomer! */
    }
    apr_pool_cleanup_register(pconf, NULL, remove_lock, apr_pool_cleanup_null);

    errmsg = socache_provider->create(&socache_instance, NULL, ptmp, pconf);
    if (errmsg) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, "%s", errmsg);
        return 500; /* An HTTP status would be a misnomer! */
    }

    rv = socache_provider->init(socache_instance, authn_cache_id,
                                &authn_cache_hints, s, pconf);
    if (rv != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog,
                      "failed to initialise %s cache", authn_cache_id);
        return 500; /* An HTTP status would be a misnomer! */
    }
    apr_pool_cleanup_register(pconf, (void*)s, destroy_cache, apr_pool_cleanup_null);
    return OK;
}
static void authn_cache_child_init(apr_pool_t *p, server_rec *s)
{
    const char *lock = apr_global_mutex_lockfile(authn_cache_mutex);
    apr_status_t rv;
    if (!configured) {
        return;       /* don't waste the overhead of creating mutex & cache */
    }
    rv = apr_global_mutex_child_init(&authn_cache_mutex, lock, p);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "failed to initialise mutex in child_init");
    }
}

static const char *authn_cache_socache(cmd_parms *cmd, void *CFG,
                                       const char *arg)
{
    const char *errmsg = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    socache_provider = ap_lookup_provider(AP_SOCACHE_PROVIDER_GROUP, arg,
                                          AP_SOCACHE_PROVIDER_VERSION);
    if (socache_provider == NULL) {
        errmsg = "Unknown socache provider";
    }
    return errmsg;
}

static const char *const directory = "directory";
static void* authn_cache_dircfg_create(apr_pool_t *pool, char *s)
{
    authn_cache_dircfg *ret = apr_palloc(pool, sizeof(authn_cache_dircfg));
    ret->timeout = apr_time_from_sec(300);
    ret->providers = NULL;
