    apr_file_t *tmpfile;

    if (strcasecmp(type, "disk")) {
	return DECLINED;
    }

    /* Allocate and initialize cache_object_t and disk_cache_object_t */
    obj = apr_pcalloc(r->pool, sizeof(*obj));
    obj->vobj = dobj = apr_pcalloc(r->pool, sizeof(*dobj));

    obj->key = apr_pstrdup(r->pool, key);
    obj->info.len = len;
    obj->complete = 0;   /* Cache object is not complete */

    dobj->name = obj->key;

    /* open temporary file */
    dobj->tempfile = apr_pstrcat(r->pool, conf->cache_root, AP_TEMPFILE, NULL);
    rv = apr_file_mktemp(&tmpfile, dobj->tempfile,  
                         APR_CREATE | APR_READ | APR_WRITE | APR_EXCL, r->pool);

    /* Populate the cache handle */
    h->cache_obj = obj;
    h->read_body = &read_body;
    h->read_headers = &read_headers;
    h->write_body = &write_body;
    h->write_headers = &write_headers;
    h->remove_entity = &remove_entity;

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "disk_cache: Caching URL %s",  key);

    return OK;
}

static int open_entity(cache_handle_t *h, request_rec *r, const char *type, const char *key)
{
    apr_status_t rc;
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config, 
                                                 &disk_cache_module);
    char *data = data_file(r->pool, conf->dirlevels, conf->dirlength, 
                           conf->cache_root, key);
    char *headers = header_file(r->pool, conf->dirlevels, conf->dirlength, 
                                conf->cache_root, key);
    apr_file_t *fd;
    apr_file_t *hfd;
    apr_finfo_t finfo;
    cache_object_t *obj;
    cache_info *info;
    disk_cache_object_t *dobj;
