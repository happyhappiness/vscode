static apr_status_t store_body(cache_handle_t *h, request_rec *r,
                               apr_bucket_brigade *bb)
{
    apr_bucket *e;
    apr_status_t rv;
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &disk_cache_module);

    /* We write to a temp file and then atomically rename the file over
     * in file_cache_el_final().
     */
    if (!dobj->tfd) {
        rv = apr_file_mktemp(&dobj->tfd, dobj->tempfile,
                             APR_CREATE | APR_WRITE | APR_BINARY |
                             APR_BUFFERED | APR_EXCL, r->pool);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        dobj->file_size = 0;
    }

    for (e = APR_BRIGADE_FIRST(bb);
         e != APR_BRIGADE_SENTINEL(bb);
         e = APR_BUCKET_NEXT(e))
    {
        const char *str;
        apr_size_t length, written;
        rv = apr_bucket_read(e, &str, &length, APR_BLOCK_READ);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "cache_disk: Error when reading bucket for URL %s",
                         h->cache_obj->key);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            file_cache_errorcleanup(dobj, r);
            return rv;
        }
        rv = apr_file_write_full(dobj->tfd, str, length, &written);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "cache_disk: Error when writing cache file for URL %s",
                         h->cache_obj->key);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            file_cache_errorcleanup(dobj, r);
            return rv;
        }
        dobj->file_size += written;
        if (dobj->file_size > conf->maxfs) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache_disk: URL %s failed the size check "
                         "(%" APR_OFF_T_FMT ">%" APR_SIZE_T_FMT ")",
                         h->cache_obj->key, dobj->file_size, conf->maxfs);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            file_cache_errorcleanup(dobj, r);
            return APR_EGENERAL;
        }
    }

    /* Was this the final bucket? If yes, close the temp file and perform
     * sanity checks.
     */
    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
        if (r->connection->aborted || r->no_cache) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "disk_cache: Discarding body for URL %s "
                         "because connection has been aborted.",
                         h->cache_obj->key);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            file_cache_errorcleanup(dobj, r);
            return APR_EGENERAL;
        }
        if (dobj->file_size < conf->minfs) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache_disk: URL %s failed the size check "
                         "(%" APR_OFF_T_FMT "<%" APR_SIZE_T_FMT ")",
                         h->cache_obj->key, dobj->file_size, conf->minfs);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            file_cache_errorcleanup(dobj, r);
            return APR_EGENERAL;
        }

        /* All checks were fine. Move tempfile to final destination */
        /* Link to the perm file, and close the descriptor */
        file_cache_el_final(dobj, r);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "disk_cache: Body for URL %s cached.",  dobj->name);
    }

    return APR_SUCCESS;
}