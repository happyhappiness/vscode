static int cache_status(cache_handle_t *h, request_rec *r,
        apr_table_t *headers, ap_cache_status_e status, const char *reason)
{
    cache_server_conf
            *conf =
                    (cache_server_conf *) ap_get_module_config(r->server->module_config,
                            &cache_module);

    cache_dir_conf *dconf = ap_get_module_config(r->per_dir_config, &cache_module);
    int x_cache = 0, x_cache_detail = 0;

    switch (status) {
    case AP_CACHE_HIT: {
        apr_table_setn(r->subprocess_env, AP_CACHE_HIT_ENV, reason);
        break;
    }
    case AP_CACHE_REVALIDATE: {
        apr_table_setn(r->subprocess_env, AP_CACHE_REVALIDATE_ENV, reason);
        break;
    }
    case AP_CACHE_MISS: {
        apr_table_setn(r->subprocess_env, AP_CACHE_MISS_ENV, reason);
        break;
    }
    case AP_CACHE_INVALIDATE: {
        apr_table_setn(r->subprocess_env, AP_CACHE_INVALIDATE_ENV, reason);
        break;
    }
    }

    apr_table_setn(r->subprocess_env, AP_CACHE_STATUS_ENV, reason);

    if (dconf && dconf->x_cache_set) {
        x_cache = dconf->x_cache;
    }
    else {
        x_cache = conf->x_cache;
    }
    if (x_cache) {
        apr_table_setn(headers, "X-Cache", apr_psprintf(r->pool, "%s from %s",
                status == AP_CACHE_HIT ? "HIT"
                        : status == AP_CACHE_REVALIDATE ? "REVALIDATE" : status
                                == AP_CACHE_INVALIDATE ? "INVALIDATE" : "MISS",
                r->server->server_hostname));
    }

    if (dconf && dconf->x_cache_detail_set) {
        x_cache_detail = dconf->x_cache_detail;
    }
    else {
        x_cache_detail = conf->x_cache_detail;
    }
    if (x_cache_detail) {
        apr_table_setn(headers, "X-Cache-Detail", apr_psprintf(r->pool,
                "\"%s\" from %s", reason, r->server->server_hostname));
    }

    return OK;
}