static apr_status_t store_body(cache_handle_t *h, request_rec *r,
                               apr_bucket_brigade *in, apr_bucket_brigade *out)
{
    apr_bucket *e;
    apr_status_t rv = APR_SUCCESS;
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    disk_cache_dir_conf *dconf = ap_get_module_config(r->per_dir_config, &cache_disk_module);
    int seen_eos = 0;

    if (!dobj->offset) {
        dobj->offset = dconf->readsize;
    }
    if (!dobj->timeout && dconf->readtime) {
        dobj->timeout = apr_time_now() + dconf->readtime;
    }

    if (dobj->offset) {
        apr_brigade_partition(in, dobj->offset, &e);
    }

    while (APR_SUCCESS == rv && !APR_BRIGADE_EMPTY(in)) {
        const char *str;
        apr_size_t length, written;

        e = APR_BRIGADE_FIRST(in);

        /* are we done completely? if so, pass any trailing buckets right through */
        if (dobj->done || !dobj->data.pool) {
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(out, e);
            continue;
        }

        /* have we seen eos yet? */
        if (APR_BUCKET_IS_EOS(e)) {
            seen_eos = 1;
            dobj->done = 1;
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
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00730)
                    "Error when reading bucket for URL %s",
                    h->cache_obj->key);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            apr_pool_destroy(dobj->data.pool);
            return rv;
        }

        /* don't write empty buckets to the cache */
        if (!length) {
            continue;
        }

        if (!dobj->disk_info.header_only) {

            /* Attempt to create the data file at the last possible moment, if
             * the body is empty, we don't write a file at all, and save an inode.
             */
            if (!dobj->data.tempfd) {
                apr_finfo_t finfo;
                rv = apr_file_mktemp(&dobj->data.tempfd, dobj->data.tempfile,
                        APR_CREATE | APR_WRITE | APR_BINARY | APR_BUFFERED
                                | APR_EXCL, dobj->data.pool);
                if (rv != APR_SUCCESS) {
                    apr_pool_destroy(dobj->data.pool);
                    return rv;
                }
                dobj->file_size = 0;
                rv = apr_file_info_get(&finfo, APR_FINFO_IDENT,
                        dobj->data.tempfd);
                if (rv != APR_SUCCESS) {
                    apr_pool_destroy(dobj->data.pool);
                    return rv;
                }
                dobj->disk_info.device = finfo.device;
                dobj->disk_info.inode = finfo.inode;
                dobj->disk_info.has_body = 1;
            }

            /* write to the cache, leave if we fail */
            rv = apr_file_write_full(dobj->data.tempfd, str, length, &written);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(
                        APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00731) "Error when writing cache file for URL %s", h->cache_obj->key);
                /* Remove the intermediate cache file and return non-APR_SUCCESS */
                apr_pool_destroy(dobj->data.pool);
                return rv;
            }
            dobj->file_size += written;
            if (dobj->file_size > dconf->maxfs) {
                ap_log_rerror(
                        APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00732) "URL %s failed the size check "
                        "(%" APR_OFF_T_FMT ">%" APR_OFF_T_FMT ")", h->cache_obj->key, dobj->file_size, dconf->maxfs);
                /* Remove the intermediate cache file and return non-APR_SUCCESS */
                apr_pool_destroy(dobj->data.pool);
                return APR_EGENERAL;
            }

        }

        /* have we reached the limit of how much we're prepared to write in one
         * go? If so, leave, we'll get called again. This prevents us from trying
         * to swallow too much data at once, or taking so long to write the data
         * the client times out.
         */
        dobj->offset -= length;
        if (dobj->offset <= 0) {
            dobj->offset = 0;
            break;
        }
        if ((dconf->readtime && apr_time_now() > dobj->timeout)) {
            dobj->timeout = 0;
            break;
        }

    }

    /* Was this the final bucket? If yes, close the temp file and perform
     * sanity checks.
     */
    if (seen_eos) {
        const char *cl_header = apr_table_get(r->headers_out, "Content-Length");

        if (!dobj->disk_info.header_only) {

            if (dobj->data.tempfd) {
                rv = apr_file_close(dobj->data.tempfd);
                if (rv != APR_SUCCESS) {
                    /* Buffered write failed, abandon attempt to write */
                    apr_pool_destroy(dobj->data.pool);
                    return rv;
                }
            }

            if (r->connection->aborted || r->no_cache) {
                ap_log_rerror(
                        APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00733) "Discarding body for URL %s "
                        "because connection has been aborted.", h->cache_obj->key);
                /* Remove the intermediate cache file and return non-APR_SUCCESS */
                apr_pool_destroy(dobj->data.pool);
                return APR_EGENERAL;
            }
            if (dobj->file_size < dconf->minfs) {
                ap_log_rerror(
                        APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00734) "URL %s failed the size check "
                        "(%" APR_OFF_T_FMT "<%" APR_OFF_T_FMT ")", h->cache_obj->key, dobj->file_size, dconf->minfs);
                /* Remove the intermediate cache file and return non-APR_SUCCESS */
                apr_pool_destroy(dobj->data.pool);
                return APR_EGENERAL;
            }
            if (cl_header) {
                apr_int64_t cl = apr_atoi64(cl_header);
                if ((errno == 0) && (dobj->file_size != cl)) {
                    ap_log_rerror(
                            APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00735) "URL %s didn't receive complete response, not caching", h->cache_obj->key);
                    /* Remove the intermediate cache file and return non-APR_SUCCESS */
                    apr_pool_destroy(dobj->data.pool);
                    return APR_EGENERAL;
                }
            }

        }

        /* All checks were fine, we're good to go when the commit comes */
    }

    return APR_SUCCESS;
}