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