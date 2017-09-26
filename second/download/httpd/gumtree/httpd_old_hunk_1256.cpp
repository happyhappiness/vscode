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
