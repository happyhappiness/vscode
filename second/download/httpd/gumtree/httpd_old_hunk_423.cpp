    obj->complete = 0;   /* Cache object is not complete */

    dobj->name = obj->key;

    /* open temporary file */
    dobj->tempfile = apr_pstrcat(r->pool, conf->cache_root, AP_TEMPFILE, NULL);
    rv = apr_file_mktemp(&tmpfile, dobj->tempfile,  
                         APR_CREATE | APR_READ | APR_WRITE | APR_EXCL, r->pool);

    if (rv == APR_SUCCESS) {
        /* Populate the cache handle */
        h->cache_obj = obj;
        h->read_body = &read_body;
        h->read_headers = &read_headers;
        h->write_body = &write_body;
        h->write_headers = &write_headers;
        h->remove_entity = &remove_entity;

        ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "disk_cache: Caching URL %s",  key);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                     "disk_cache: Could not cache URL %s [%d]", key, rv);

        return DECLINED;
    }

    return OK;
}

static int open_entity(cache_handle_t *h, request_rec *r, const char *type, const char *key)
{
    apr_status_t rc;
    static int error_logged = 0;
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config, 
                                                 &disk_cache_module);
    char *data;
    char *headers;
    apr_file_t *fd;
    apr_file_t *hfd;
    apr_finfo_t finfo;
    cache_object_t *obj;
    cache_info *info;
    disk_cache_object_t *dobj;

    h->cache_obj = NULL;

    /* Look up entity keyed to 'url' */
    if (strcasecmp(type, "disk")) {
        return DECLINED;
    }

    if (conf->cache_root == NULL) {
        if (!error_logged) {
            error_logged = 1;
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                         "disk_cache: Cannot cache files to disk without a CacheRoot specified.");
        }
        return DECLINED;
    }

    data = data_file(r->pool, conf->dirlevels, conf->dirlength, 
                     conf->cache_root, key);
    headers = header_file(r->pool, conf->dirlevels, conf->dirlength, 
                          conf->cache_root, key);

    /* Open the data file */
    rc = apr_file_open(&fd, data, APR_READ|APR_BINARY, 0, r->pool);
    if (rc != APR_SUCCESS) {
        /* XXX: Log message */
        return DECLINED;
    }

    /* Open the headers file */
    rc = apr_file_open(&hfd, headers, APR_READ|APR_BINARY, 0, r->pool);
    if (rc != APR_SUCCESS) {
        /* XXX: Log message */
        return DECLINED;
    }

    /* Create and init the cache object */
    h->cache_obj = obj = apr_pcalloc(r->pool, sizeof(cache_object_t));
    obj->vobj = dobj = apr_pcalloc(r->pool, sizeof(disk_cache_object_t));

    info = &(obj->info);
    obj->key = (char *) key;
    dobj->name = (char *) key;
    dobj->fd = fd;
    dobj->hfd = hfd;
    dobj->datafile = data;
    dobj->hdrsfile = headers;

    rc = apr_file_info_get(&finfo, APR_FINFO_SIZE, fd);
    if (rc == APR_SUCCESS) {
        dobj->file_size = finfo.size;
    }
    
    /* Read the bytes to setup the cache_info fields */
    rc = file_cache_read_mydata(hfd, info, dobj);
    if (rc != APR_SUCCESS) {
        /* XXX log message */
        return DECLINED;
    }

    /* Initialize the cache_handle callback functions */
    h->read_body = &read_body;
    h->read_headers = &read_headers;
    h->write_body = &write_body;
    h->write_headers = &write_headers;
    h->remove_entity = &remove_entity;

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "disk_cache: Serving Cached URL %s",  dobj->name);
    return OK;
}

static int remove_entity(cache_handle_t *h) 
{
    /* Null out the cache object pointer so next time we start from scratch  */
    h->cache_obj = NULL;
    return OK;
}

/*
 * Reads headers from a buffer and returns an array of headers.
 * Returns NULL on file error
 * This routine tries to deal with too long lines and continuation lines.
 * @@@: XXX: FIXME: currently the headers are passed thru un-merged. 
 * Is that okay, or should they be collapsed where possible?
 */
static apr_status_t read_headers(cache_handle_t *h, request_rec *r) 
{
    apr_status_t rv;
    char urlbuff[1034];
    int urllen = sizeof(urlbuff);
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    apr_table_t * tmp;

    /* This case should not happen... */
    if (!dobj->fd || !dobj->hfd) {
        /* XXX log message */
        return APR_NOTFOUND; 
    }

    if(!r->headers_out) {
        r->headers_out = apr_table_make(r->pool, 20);
    }
    
    /*
     * Call routine to read the header lines/status line 
     */
    ap_scan_script_header_err(r, dobj->hfd, NULL);
 
    apr_table_setn(r->headers_out, "Content-Type", 
                   ap_make_content_type(r, r->content_type));

    rv = apr_file_gets(&urlbuff[0], urllen, dobj->hfd);           /* Read status  */
    if (rv != APR_SUCCESS) {
        /* XXX log message */
	return rv;
    }

    r->status = atoi(urlbuff);                           /* Save status line into request rec  */

    /* Read and ignore the status line (This request might result in a
     * 304, so we don't necessarily want to retransmit a 200 from the cache.)
     */
    rv = apr_file_gets(&urlbuff[0], urllen, dobj->hfd);
    if (rv != APR_SUCCESS) {
        /* XXX log message */
	return rv;
    }

    h->req_hdrs = apr_table_make(r->pool, 20);
    
    /*
     * Call routine to read the header lines/status line 
     */
    tmp = r->err_headers_out;
    r->err_headers_out = h->req_hdrs;
    rv = apr_file_gets(&urlbuff[0], urllen, dobj->hfd);           /* Read status  */
    ap_scan_script_header_err(r, dobj->hfd, NULL);
    r->err_headers_out = tmp;
 
    apr_file_close(dobj->hfd);

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "disk_cache: Served headers for URL %s",  dobj->name);
    return APR_SUCCESS;
}

static apr_status_t read_body(cache_handle_t *h, apr_pool_t *p, apr_bucket_brigade *bb) 
{
    apr_bucket *e;
    disk_cache_object_t *dobj = (disk_cache_object_t*) h->cache_obj->vobj;

    e = apr_bucket_file_create(dobj->fd, 0, (apr_size_t) dobj->file_size, p,
                               bb->bucket_alloc);
