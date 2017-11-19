static int socache_status_hook(request_rec *r, int flags)
{
    apr_status_t status = APR_SUCCESS;
    cache_socache_conf *conf = ap_get_module_config(r->server->module_config,
                                                    &cache_socache_module);
    if (!conf->provider || !conf->provider->socache_provider ||
        !conf->provider->socache_instance) {
        return DECLINED;
    }

    ap_rputs("<hr>\n"
             "<table cellspacing=0 cellpadding=0>\n"
             "<tr><td bgcolor=\"#000000\">\n"
             "<b><font color=\"#ffffff\" face=\"Arial,Helvetica\">"
             "mod_cache_socache Status:</font></b>\n"
             "</td></tr>\n"
             "<tr><td bgcolor=\"#ffffff\">\n", r);

    if (socache_mutex) {
        status = apr_global_mutex_lock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02816)
                    "could not acquire lock for cache status");
        }
    }

    if (status != APR_SUCCESS) {
        ap_rputs("No cache status data available\n", r);
    } else {
        conf->provider->socache_provider->status(conf->provider->socache_instance,
                                                 r, flags);
    }

    if (socache_mutex && status == APR_SUCCESS) {
        status = apr_global_mutex_unlock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02817)
                    "could not release lock for cache status");
        }
    }

    ap_rputs("</td></tr>\n</table>\n", r);
    return OK;
}