    obj->complete = 0;   /* Cache object is not complete */

    dobj->name = obj->key;

    /* open temporary file */
    dobj->tempfile = apr_pstrcat(r->pool, conf->cache_root, AP_TEMPFILE, NULL);
    rv = apr_file_mktemp(&tmpfile, dobj->tempfile,
                         APR_CREATE | APR_READ | APR_WRITE | APR_EXCL, r->pool);

    if (rv == APR_SUCCESS) {
        /* Populate the cache handle */
        h->cache_obj = obj;

        ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "disk_cache: Storing URL %s",  key);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "disk_cache: Could not store URL %s [%d]", key, rv);

        return DECLINED;
    }

    return OK;
}

static int open_entity(cache_handle_t *h, request_rec *r, const char *key)
{
    apr_status_t rc;
    static int error_logged = 0;
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &disk_cache_module);
    apr_finfo_t finfo;
    cache_object_t *obj;
    cache_info *info;
    disk_cache_object_t *dobj;
    int flags;

    h->cache_obj = NULL;

    /* Look up entity keyed to 'url' */
    if (conf->cache_root == NULL) {
        if (!error_logged) {
            error_logged = 1;
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "disk_cache: Cannot cache files to disk without a CacheRoot specified.");
        }
        return DECLINED;
    }


    /* Create and init the cache object */
    h->cache_obj = obj = apr_pcalloc(r->pool, sizeof(cache_object_t));
    obj->vobj = dobj = apr_pcalloc(r->pool, sizeof(disk_cache_object_t));

    info = &(obj->info);
    obj->key = (char *) key;
    dobj->name = (char *) key;
    dobj->datafile = data_file(r->pool, conf, dobj, key);
    dobj->hdrsfile = header_file(r->pool, conf, dobj, key);

    /* Open the data file */
    flags = APR_READ|APR_BINARY;
#ifdef APR_SENDFILE_ENABLED
    flags |= APR_SENDFILE_ENABLED;
#endif
    rc = apr_file_open(&dobj->fd, dobj->datafile, flags, 0, r->pool);
    if (rc != APR_SUCCESS) {
        /* XXX: Log message */
        return DECLINED;
    }

    /* Open the headers file */
    flags = APR_READ|APR_BINARY|APR_BUFFERED;
    rc = apr_file_open(&dobj->hfd, dobj->hdrsfile, flags, 0, r->pool);
    if (rc != APR_SUCCESS) {
        /* XXX: Log message */
        return DECLINED;
    }

    rc = apr_file_info_get(&finfo, APR_FINFO_SIZE, dobj->fd);
    if (rc == APR_SUCCESS) {
        dobj->file_size = finfo.size;
    }

    /* Read the bytes to setup the cache_info fields */
    rc = file_cache_recall_mydata(dobj->hfd, info, dobj, r);
    if (rc != APR_SUCCESS) {
        /* XXX log message */
        return DECLINED;
    }

    /* Initialize the cache_handle callback functions */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "disk_cache: Recalled cached URL info header %s",  dobj->name);
    return OK;
}

static int remove_entity(cache_handle_t *h)
{
    /* Null out the cache object pointer so next time we start from scratch  */
    h->cache_obj = NULL;
    return OK;
}

static int remove_url(const char *key)
{
    /* XXX: Delete file from cache! */
    return OK;
}

/*
 * Reads headers from a buffer and returns an array of headers.
 * Returns NULL on file error
 * This routine tries to deal with too long lines and continuation lines.
 * @@@: XXX: FIXME: currently the headers are passed thru un-merged.
 * Is that okay, or should they be collapsed where possible?
 */
static apr_status_t recall_headers(cache_handle_t *h, request_rec *r)
{
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    apr_table_t * tmp;

    /* This case should not happen... */
    if (!dobj->hfd) {
        /* XXX log message */
        return APR_NOTFOUND;
    }

    if(!r->headers_out) {
        r->headers_out = apr_table_make(r->pool, 20);
    }

    /*
     * Call routine to read the header lines/status line
     */
    r->status = dobj->disk_info.status;
    ap_scan_script_header_err(r, dobj->hfd, NULL);

    apr_table_setn(r->headers_out, "Content-Type",
                   ap_make_content_type(r, r->content_type));

    h->req_hdrs = apr_table_make(r->pool, 20);

    /*
     * Call routine to read the header lines/status line
     *
     * Note that ap_scan_script_header_err sets to r->err_headers_out,
     * so we must set the real one aside.
     */
    tmp = r->err_headers_out;
    r->err_headers_out = h->req_hdrs;
    ap_scan_script_header_err(r, dobj->hfd, NULL);
    r->err_headers_out = tmp;

    apr_file_close(dobj->hfd);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "disk_cache: Recalled headers for URL %s",  dobj->name);
    return APR_SUCCESS;
}

static apr_status_t recall_body(cache_handle_t *h, apr_pool_t *p, apr_bucket_brigade *bb)
{
    apr_bucket *e;
    disk_cache_object_t *dobj = (disk_cache_object_t*) h->cache_obj->vobj;

    e = apr_bucket_file_create(dobj->fd, 0, (apr_size_t) dobj->file_size, p,
                               bb->bucket_alloc);
