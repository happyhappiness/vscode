        apr_file_close(hfd); /* flush and close */
    }
    else {
        /* XXX log message */
    }

    ap_log_error(APLOG_MARK, APLOG_INFO|APLOG_NOERRNO, 0, r->server,
                 "disk_cache: Caching headers for URL %s",  dobj->name);
    return APR_SUCCESS;
}
static apr_status_t write_body(cache_handle_t *h, request_rec *r, apr_bucket_brigade *b) 
{
    apr_bucket *e;
    apr_status_t rv;
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    cache_info *info = &(h->cache_obj->info);

    if (!dobj->fd) {
        rv = apr_file_open(&dobj->fd, dobj->tempfile, 
                           APR_WRITE | APR_CREATE | APR_BINARY| APR_TRUNCATE | APR_BUFFERED,
                           APR_UREAD | APR_UWRITE, r->pool);
        if (rv != APR_SUCCESS) {
