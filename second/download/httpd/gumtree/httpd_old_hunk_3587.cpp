    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00763)
            "cache: running CACHE_OUT filter");

    /* clean out any previous response up to EOS, if any */
    for (e = APR_BRIGADE_FIRST(in);
         e != APR_BRIGADE_SENTINEL(in);
         e = APR_BUCKET_NEXT(e))
    {
        if (APR_BUCKET_IS_EOS(e)) {
            apr_bucket_brigade *bb = apr_brigade_create(r->pool,
                    r->connection->bucket_alloc);

            /* restore content type of cached response if available */
            /* Needed especially when stale content gets served. */
