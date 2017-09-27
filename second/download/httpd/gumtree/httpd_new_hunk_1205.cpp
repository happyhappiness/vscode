         e = APR_BUCKET_NEXT(e))
    {
        const char *s;
        apr_size_t len;

        if (APR_BUCKET_IS_EOS(e)) {
            const char *cl_header = apr_table_get(r->headers_out, "Content-Length");
            if (cl_header) {
                apr_int64_t cl = apr_atoi64(cl_header);
                if ((errno == 0) && (obj->count != cl)) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                 "mem_cache: URL %s didn't receive complete response, not caching",
                                 h->cache_obj->key);
                    return APR_EGENERAL;
                }
            }
            if (mobj->m_len > obj->count) {
                /* Caching a streamed response. Reallocate a buffer of the
                 * correct size and copy the streamed response into that
                 * buffer */
                mobj->m = realloc(mobj->m, obj->count);
                if (!mobj->m) {
