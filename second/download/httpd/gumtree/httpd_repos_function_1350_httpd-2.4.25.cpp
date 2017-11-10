static int socache_post_config(apr_pool_t *pconf, apr_pool_t *plog,
        apr_pool_t *ptmp, server_rec *base_server)
{
    server_rec *s;
    apr_status_t rv;
    const char *errmsg;
    static struct ap_socache_hints socache_hints =
    { 64, 2048, 60000000 };

    for (s = base_server; s; s = s->next) {
        cache_socache_conf *conf =
                ap_get_module_config(s->module_config, &cache_socache_module);

        if (!conf->provider) {
            continue;
        }

        if (!socache_mutex && conf->provider->socache_provider->flags
                & AP_SOCACHE_FLAG_NOTMPSAFE) {

            rv = ap_global_mutex_create(&socache_mutex, NULL, cache_socache_id,
                    NULL, s, pconf, 0);
            if (rv != APR_SUCCESS) {
                ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(02391)
                "failed to create %s mutex", cache_socache_id);
                return 500; /* An HTTP status would be a misnomer! */
            }
            apr_pool_cleanup_register(pconf, NULL, remove_lock,
                    apr_pool_cleanup_null);
        }

        errmsg = conf->provider->socache_provider->create(
                &conf->provider->socache_instance, conf->provider->args, ptmp,
                pconf);
        if (errmsg) {
            ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, plog,
                    APLOGNO(02392) "%s", errmsg);
            return 500; /* An HTTP status would be a misnomer! */
        }

        rv = conf->provider->socache_provider->init(
                conf->provider->socache_instance, cache_socache_id,
                &socache_hints, s, pconf);
        if (rv != APR_SUCCESS) {
            ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(02393)
            "failed to initialise %s cache", cache_socache_id);
            return 500; /* An HTTP status would be a misnomer! */
        }
        apr_pool_cleanup_register(pconf, (void *) s, destroy_cache,
                apr_pool_cleanup_null);

    }

    return OK;
}