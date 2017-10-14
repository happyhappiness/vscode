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
                         "cache_disk: URL %s failed the size check (%lu>%lu)",
                         h->cache_obj->key, (unsigned long)dobj->file_size,
                         (unsigned long)conf->maxfs);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            file_cache_errorcleanup(dobj, r);
            return APR_EGENERAL;
        }
    }

    /* Was this the final bucket? If yes, close the temp file and perform
     * sanity checks.
     */
    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
        if (h->cache_obj->info.len <= 0) {
          /* If the target value of the content length is unknown
           * (h->cache_obj->info.len <= 0), check if connection has been
           * aborted by client to avoid caching incomplete request bodies.
           *
           * This can happen with large responses from slow backends like
           * Tomcat via mod_jk.
           */
          if (r->connection->aborted) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "disk_cache: Discarding body for URL %s "
                         "because connection has been aborted.",
                         h->cache_obj->key);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            file_cache_errorcleanup(dobj, r);
            return APR_EGENERAL;
          }
          /* XXX Fixme: file_size isn't constrained by size_t. */
          h->cache_obj->info.len = dobj->file_size;
        }
        else if (h->cache_obj->info.len != dobj->file_size) {
          /* "Content-Length" and actual content disagree in size. Log that. */
          ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                       "disk_cache: URL %s failed the size check (%lu != %lu)",
                       h->cache_obj->key,
                       (unsigned long)h->cache_obj->info.len,
                       (unsigned long)dobj->file_size);
          /* Remove the intermediate cache file and return non-APR_SUCCESS */
          file_cache_errorcleanup(dobj, r);
          return APR_EGENERAL;
        }
        if (dobj->file_size < conf->minfs) {
          ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache_disk: URL %s failed the size check (%lu<%lu)",
                     h->cache_obj->key, (unsigned long)dobj->file_size, (unsigned long)conf->minfs);
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