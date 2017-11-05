static apr_status_t store_body(cache_handle_t *h, request_rec *r,
        apr_bucket_brigade *in, apr_bucket_brigade *out)
{
    apr_bucket *e;
    apr_status_t rv = APR_SUCCESS;
    cache_socache_object_t *sobj =
            (cache_socache_object_t *) h->cache_obj->vobj;
    cache_socache_dir_conf *dconf =
            ap_get_module_config(r->per_dir_config, &cache_socache_module);
    int seen_eos = 0;

    if (!sobj->offset) {
        sobj->offset = dconf->readsize;
    }
    if (!sobj->timeout && dconf->readtime) {
        sobj->timeout = apr_time_now() + dconf->readtime;
    }

    if (!sobj->newbody) {
        if (sobj->body) {
            apr_brigade_cleanup(sobj->body);
        }
        else {
            sobj->body = apr_brigade_create(r->pool,
                    r->connection->bucket_alloc);
        }
        sobj->newbody = 1;
    }
    if (sobj->offset) {
        apr_brigade_partition(in, sobj->offset, &e);
    }

    while (APR_SUCCESS == rv && !APR_BRIGADE_EMPTY(in)) {
        const char *str;
        apr_size_t length;

        e = APR_BRIGADE_FIRST(in);

        /* are we done completely? if so, pass any trailing buckets right through */
        if (sobj->done || !sobj->pool) {
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(out, e);
            continue;
        }

        /* have we seen eos yet? */
        if (APR_BUCKET_IS_EOS(e)) {
            seen_eos = 1;
            sobj->done = 1;
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(out, e);
            break;
        }

        /* honour flush buckets, we'll get called again */
        if (APR_BUCKET_IS_FLUSH(e)) {
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(out, e);
            break;
        }

        /* metadata buckets are preserved as is */
        if (APR_BUCKET_IS_METADATA(e)) {
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(out, e);
            continue;
        }

        /* read the bucket, write to the cache */
        rv = apr_bucket_read(e, &str, &length, APR_BLOCK_READ);
        APR_BUCKET_REMOVE(e);
        APR_BRIGADE_INSERT_TAIL(out, e);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02377)
                    "Error when reading bucket for URL %s",
                    h->cache_obj->key);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return rv;
        }

        /* don't write empty buckets to the cache */
        if (!length) {
            continue;
        }

        sobj->file_size += length;
        if (sobj->file_size >= sobj->buffer_len - sobj->body_offset) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02378)
                    "URL %s failed the buffer size check "
                    "(%" APR_OFF_T_FMT ">=%" APR_SIZE_T_FMT ")",
                    h->cache_obj->key, sobj->file_size, sobj->buffer_len - sobj->body_offset);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return APR_EGENERAL;
        }

        rv = apr_bucket_copy(e, &e);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02379)
                    "Error when copying bucket for URL %s",
                    h->cache_obj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return rv;
        }
        APR_BRIGADE_INSERT_TAIL(sobj->body, e);

        /* have we reached the limit of how much we're prepared to write in one
         * go? If so, leave, we'll get called again. This prevents us from trying
         * to swallow too much data at once, or taking so long to write the data
         * the client times out.
         */
        sobj->offset -= length;
        if (sobj->offset <= 0) {
            sobj->offset = 0;
            break;
        }
        if ((dconf->readtime && apr_time_now() > sobj->timeout)) {
            sobj->timeout = 0;
            break;
        }

    }

    /* Was this the final bucket? If yes, perform sanity checks.
     */
    if (seen_eos) {
        const char *cl_header = apr_table_get(r->headers_out, "Content-Length");

        if (r->connection->aborted || r->no_cache) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02380)
                    "Discarding body for URL %s "
                    "because connection has been aborted.",
                    h->cache_obj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return APR_EGENERAL;
        }
        if (cl_header) {
            apr_int64_t cl = apr_atoi64(cl_header);
            if ((errno == 0) && (sobj->file_size != cl)) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02381)
                        "URL %s didn't receive complete response, not caching",
                        h->cache_obj->key);
                apr_pool_destroy(sobj->pool);
                sobj->pool = NULL;
                return APR_EGENERAL;
            }
        }

        /* All checks were fine, we're good to go when the commit comes */

    }

    return APR_SUCCESS;
}