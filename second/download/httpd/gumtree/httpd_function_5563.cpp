int ap_cache_check_no_store(cache_request_rec *cache, request_rec *r)
{

    cache_server_conf *conf =
      (cache_server_conf *)ap_get_module_config(r->server->module_config,
                                                &cache_module);

    /*
     * At this point, we may have data cached, but the request may have
     * specified that cached data may not be used in a response.
     *
     * - RFC2616 14.9.2 What May be Stored by Caches. If Cache-Control:
     * no-store arrives, do not serve from or store to the cache.
     */

    /* This value comes from the client's initial request. */
    if (!cache->control_in.parsed) {
        const char *cc_req = cache_table_getm(r->pool, r->headers_in,
                "Cache-Control");
        const char *pragma = cache_table_getm(r->pool, r->headers_in, "Pragma");
        ap_cache_control(r, &cache->control_in, cc_req, pragma, r->headers_in);
    }

    if (cache->control_in.no_store) {

        if (!conf->ignorecachecontrol) {
            /* We're not allowed to serve a cached copy */
            return 0;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                    "Incoming request is asking for a no-store version of "
                    "%s, but we have been configured to ignore it and serve "
                    "cached content anyway", r->unparsed_uri);
        }
    }

    return 1;
}