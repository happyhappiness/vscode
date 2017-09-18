     */

    rv = cache_select_url(r, cache->types, url);
    if (DECLINED == rv) {
        if (!lookup) {
            /* no existing cache file */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: no cache - add cache_in filter and DECLINE");
            /* add cache_in filter to cache this request */
            ap_add_output_filter("CACHE_IN", NULL, r, r->connection);
        }
        return DECLINED;
    }
    else if (OK == rv) {
        /* RFC2616 13.2 - Check cache object expiration */
        cache->fresh = ap_cache_check_freshness(cache, r);
        if (cache->fresh) {
            /* fresh data available */
            apr_bucket_brigade *out;
            conn_rec *c = r->connection;

            if (lookup) {
                return OK;
            }
            rv = ap_meets_conditions(r);
            if (rv != OK) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "cache: fresh cache - returning status %d", rv);
                return rv;
            }

            /*
             * Not a conditionl request. Serve up the content 
             */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache: fresh cache - add cache_out filter and "
                         "handle request");

            /* We are in the quick handler hook, which means that no output
             * filters have been set. So lets run the insert_filter hook.
             */
            ap_run_insert_filter(r);
            ap_add_output_filter("CACHE_OUT", NULL, r, r->connection);

            /* kick off the filter stack */
            out = apr_brigade_create(r->pool, c->bucket_alloc);
            if (APR_SUCCESS != (rv = ap_pass_brigade(r->output_filters, out))) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
