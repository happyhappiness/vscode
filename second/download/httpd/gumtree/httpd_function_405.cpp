static apr_status_t write_body(cache_handle_t *h, request_rec *r, apr_bucket_brigade *b) 
{
    apr_bucket *e;
    apr_status_t rv;
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;

    if (!dobj->fd) {
        rv = apr_file_open(&dobj->fd, dobj->tempfile, 
                           APR_WRITE | APR_CREATE | APR_BINARY| APR_TRUNCATE | APR_BUFFERED,
                           APR_UREAD | APR_UWRITE, r->pool);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }
    APR_BRIGADE_FOREACH(e, b) {
        const char *str;
        apr_size_t length;
        apr_bucket_read(e, &str, &length, APR_BLOCK_READ);
        apr_file_write(dobj->fd, str, &length);
    }
    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(b))) {
        file_cache_el_final(h, r);    /* Link to the perm file, and close the descriptor  */
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "disk_cache: Cached body for URL %s",  dobj->name);
    }

    return APR_SUCCESS;	
}