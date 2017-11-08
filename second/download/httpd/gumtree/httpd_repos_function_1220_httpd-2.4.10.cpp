static apr_status_t cache_out_filter(ap_filter_t *f, apr_bucket_brigade *in)
{
    request_rec *r = f->r;
    apr_bucket *e;
    cache_request_rec *cache = (cache_request_rec *)f->ctx;

    if (!cache) {
        /* user likely configured CACHE_OUT manually; they should use mod_cache
         * configuration to do that */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00762)
                "CACHE/CACHE_OUT filter enabled while caching is disabled, ignoring");
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, in);
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
            const char *ct = apr_table_get(cache->handle->resp_hdrs, "Content-Type");
            if (ct) {
                ap_set_content_type(r, ct);
            }

            /* restore status of cached response */
            r->status = cache->handle->cache_obj->info.status;

            /* recall_headers() was called in cache_select() */
            cache->provider->recall_body(cache->handle, r->pool, bb);
            APR_BRIGADE_PREPEND(in, bb);

            /* This filter is done once it has served up its content */
            ap_remove_output_filter(f);

            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00764)
                    "cache: serving %s", r->uri);
            return ap_pass_brigade(f->next, in);

        }
        apr_bucket_delete(e);
    }

    return APR_SUCCESS;
}