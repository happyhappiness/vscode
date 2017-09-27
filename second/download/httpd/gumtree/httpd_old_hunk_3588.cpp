                conf->provider->socache_instance, s);
        conf->provider->socache_instance = NULL;
    }
    return APR_SUCCESS;
}

static int socache_precfg(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptmp)
{
    apr_status_t rv = ap_mutex_register(pconf, cache_socache_id, NULL,
            APR_LOCK_DEFAULT, 0);
    if (rv != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(02390)
        "failed to register %s mutex", cache_socache_id);
        return 500; /* An HTTP status would be a misnomer! */
    }
    return OK;
}

static int socache_post_config(apr_pool_t *pconf, apr_pool_t *plog,
        apr_pool_t *ptmp, server_rec *base_server)
{
    server_rec *s;
    apr_status_t rv;
    const char *errmsg;
    static struct ap_socache_hints socache_hints =
    { 64, 32, 60000000 };

    for (s = base_server; s; s = s->next) {
        cache_socache_conf *conf =
                ap_get_module_config(s->module_config, &cache_socache_module);

        if (!conf->provider) {
