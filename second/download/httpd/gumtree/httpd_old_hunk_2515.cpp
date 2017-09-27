
        lockname = apr_pstrcat(r->pool, conf->lockpath, dir, "/", lockname, NULL);
    }
    return apr_file_remove(lockname, r->pool);
}

CACHE_DECLARE(int) ap_cache_check_freshness(cache_handle_t *h,
                                            request_rec *r)
{
    apr_status_t status;
    apr_int64_t age, maxage_req, maxage_cresp, maxage, smaxage, maxstale;
    apr_int64_t minfresh;
    const char *cc_cresp, *cc_req;
    const char *pragma;
    const char *agestr = NULL;
    const char *expstr = NULL;
    char *val;
    apr_time_t age_c = 0;
    cache_info *info = &(h->cache_obj->info);
    const char *warn_head;
    cache_server_conf *conf =
      (cache_server_conf *)ap_get_module_config(r->server->module_config,
                                                &cache_module);

    /*
     * We now want to check if our cached data is still fresh. This depends
     * on a few things, in this order:
     *
     * - RFC2616 14.9.4 End to end reload, Cache-Control: no-cache. no-cache in
     * either the request or the cached response means that we must
     * revalidate the request unconditionally, overriding any expiration
     * mechanism. It's equivalent to max-age=0,must-revalidate.
     *
     * - RFC2616 14.32 Pragma: no-cache This is treated the same as
     * Cache-Control: no-cache.
     *
     * - RFC2616 14.9.3 Cache-Control: max-stale, must-revalidate,
     * proxy-revalidate if the max-stale request header exists, modify the
