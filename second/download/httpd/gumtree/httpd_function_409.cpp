static apr_status_t store_body(cache_handle_t *h, request_rec *r, apr_bucket_brigade *b)
{
    apr_bucket *e;
    apr_status_t rv;
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &disk_cache_module);

    if (!dobj->fd) {
        rv = apr_file_open(&dobj->fd, dobj->tempfile,
                           APR_WRITE | APR_CREATE | APR_BINARY| APR_TRUNCATE | APR_BUFFERED,
                           APR_UREAD | APR_UWRITE, r->pool);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        dobj->file_size = 0;
    }
    for (e = APR_BRIGADE_FIRST(b);
         e != APR_BRIGADE_SENTINEL(b);
         e = APR_BUCKET_NEXT(e))
    {
        const char *str;
        apr_size_t length;
        apr_bucket_read(e, &str, &length, APR_BLOCK_READ);
        if (apr_file_write(dobj->fd, str, &length) != APR_SUCCESS) {
          ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "cache_disk: Error when writing cache file for URL %s",
                     h->cache_obj->key);
          /* Remove the intermediate cache file and return non-APR_SUCCESS */
          return file_cache_errorcleanup(dobj, r);
        }
        dobj->file_size += length;
        if (dobj->file_size > conf->maxfs) {
          ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache_disk: URL %s failed the size check (%lu>%lu)",
                     h->cache_obj->key, (unsigned long)dobj->file_size, (unsigned long)conf->maxfs);
          /* Remove the intermediate cache file and return non-APR_SUCCESS */
          return file_cache_errorcleanup(dobj, r);
        }
    }

    /* Was this the final bucket? If yes, close the body file and make sanity checks */
    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(b))) {
        if (h->cache_obj->info.len <= 0) {
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
          return file_cache_errorcleanup(dobj, r);
        }
        if (dobj->file_size < conf->minfs) {
          ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache_disk: URL %s failed the size check (%lu<%lu)",
                     h->cache_obj->key, (unsigned long)dobj->file_size, (unsigned long)conf->minfs);
          /* Remove the intermediate cache file and return non-APR_SUCCESS */
          return file_cache_errorcleanup(dobj, r);
        }
        /* All checks were fine. Move tempfile to final destination */
        file_cache_el_final(h, r);    /* Link to the perm file, and close the descriptor */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "disk_cache: Body for URL %s cached.",  dobj->name);
    }

    return APR_SUCCESS;
}