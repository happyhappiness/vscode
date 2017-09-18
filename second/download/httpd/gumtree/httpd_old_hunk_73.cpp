     */

    rv = cache_select_url(r, cache->types, url);
    if (DECLINED == rv) {
        if (!lookup) {
            /* no existing cache file */
            ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                         "cache: no cache - add cache_in filter and DECLINE");
            /* add cache_in filter to cache this request */
            ap_add_output_filter("CACHE_IN", NULL, r, r->connection);
        }
        return DECLINED;
    }
    else if (OK == rv) {
        /* cache file exists */
        if (cache->fresh) {
            apr_bucket_brigade *out;
            conn_rec *c = r->connection;

            /* fresh data available */
            if (lookup) {
                return OK;
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                         "cache: fresh cache - add cache_out filter and "
                         "handle request");

            /* We are in the quick handler hook, which means that no output
             * filters have been set. So lets run the insert_filter hook.
             * XXX - Should we be inserting filters in the output stream
             * for proxy requests? Certainly we need the core filters
             * (byterange, chunking, etc.).  I can also see the need to
             * conditionally insert tag processing filters (e.g. INCLUDES).
             */
            ap_run_insert_filter(r);

            /* Now add the cache_out filter. cache_out is a FTYPE_CONTENT
             * which means it will be inserted first in the stream, which
             * is exactly what we need.
             */
            ap_add_output_filter("CACHE_OUT", NULL, r, r->connection);

            /* kick off the filter stack */
            out = apr_brigade_create(r->pool, c->bucket_alloc);
            if (APR_SUCCESS != (rv = ap_pass_brigade(r->output_filters, out))) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
