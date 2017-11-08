static int create_entity(cache_handle_t *h, request_rec *r, const char *key,
        apr_off_t len, apr_bucket_brigade *bb)
{
    cache_socache_dir_conf *dconf =
            ap_get_module_config(r->per_dir_config, &cache_socache_module);
    cache_socache_conf *conf = ap_get_module_config(r->server->module_config,
            &cache_socache_module);
    cache_object_t *obj;
    cache_socache_object_t *sobj;
    apr_size_t total;

    if (conf->provider == NULL) {
        return DECLINED;
    }

    /* we don't support caching of range requests (yet) */
    /* TODO: but we could */
    if (r->status == HTTP_PARTIAL_CONTENT) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02345)
                "URL %s partial content response not cached",
                key);
        return DECLINED;
    }

    /*
     * We have a chicken and egg problem. We don't know until we
     * attempt to store_headers just how big the response will be
     * and whether it will fit in the cache limits set. But we
     * need to make a decision now as to whether we plan to try.
     * If we make the wrong decision, we could prevent another
     * cache implementation, such as cache_disk, from getting the
     * opportunity to cache, and that would be unfortunate.
     *
     * In a series of tests, from cheapest to most expensive,
     * decide whether or not to ignore this attempt to cache,
     * with a small margin just to be sure.
     */
    if (len < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02346)
                "URL '%s' had no explicit size, ignoring", key);
        return DECLINED;
    }
    if (len > dconf->max) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02347)
                "URL '%s' body larger than limit, ignoring "
                "(%" APR_OFF_T_FMT " > %" APR_OFF_T_FMT ")",
                key, len, dconf->max);
        return DECLINED;
    }

    /* estimate the total cached size, given current headers */
    total = len + sizeof(cache_socache_info_t) + strlen(key);
    if (APR_SUCCESS != store_table(r->headers_out, NULL, dconf->max, &total)
            || APR_SUCCESS != store_table(r->headers_in, NULL, dconf->max,
                    &total)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02348)
                "URL '%s' estimated headers size larger than limit, ignoring "
                "(%" APR_SIZE_T_FMT " > %" APR_OFF_T_FMT ")",
                key, total, dconf->max);
        return DECLINED;
    }

    if (total >= dconf->max) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02349)
                "URL '%s' body and headers larger than limit, ignoring "
                "(%" APR_OFF_T_FMT " > %" APR_OFF_T_FMT ")",
                key, len, dconf->max);
        return DECLINED;
    }

    /* Allocate and initialize cache_object_t and cache_socache_object_t */
    h->cache_obj = obj = apr_pcalloc(r->pool, sizeof(*obj));
    obj->vobj = sobj = apr_pcalloc(r->pool, sizeof(*sobj));

    obj->key = apr_pstrdup(r->pool, key);
    sobj->key = obj->key;
    sobj->name = obj->key;

    return OK;
}