    for (e = APR_BRIGADE_FIRST(bb);
         e != APR_BRIGADE_SENTINEL(bb);
         e = APR_BUCKET_NEXT(e))
    {
        const char *str;
        apr_size_t length, written;
        apr_bucket_read(e, &str, &length, APR_BLOCK_READ);
        rv = apr_file_write_full(dobj->tfd, str, length, &written);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "cache_disk: Error when writing cache file for URL %s",
                         h->cache_obj->key);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            file_cache_errorcleanup(dobj, r);
            return APR_EGENERAL;
        }
        dobj->file_size += written;
        if (dobj->file_size > conf->maxfs) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache_disk: URL %s failed the size check "
                         "(%" APR_OFF_T_FMT ">%" APR_SIZE_T_FMT ")",
