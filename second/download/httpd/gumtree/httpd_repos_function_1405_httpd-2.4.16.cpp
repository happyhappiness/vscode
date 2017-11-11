static int open_entity(cache_handle_t *h, request_rec *r, const char *key)
{
    apr_uint32_t format;
    apr_size_t len;
    const char *nkey;
    apr_status_t rc;
    static int error_logged = 0;
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &cache_disk_module);
#ifdef APR_SENDFILE_ENABLED
    core_dir_config *coreconf = ap_get_core_module_config(r->per_dir_config);
#endif
    apr_finfo_t finfo;
    cache_object_t *obj;
    cache_info *info;
    disk_cache_object_t *dobj;
    int flags;
    apr_pool_t *pool;

    h->cache_obj = NULL;

    /* Look up entity keyed to 'url' */
    if (conf->cache_root == NULL) {
        if (!error_logged) {
            error_logged = 1;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00703)
                    "Cannot cache files to disk without a CacheRoot specified.");
        }
        return DECLINED;
    }

    /* Create and init the cache object */
    obj = apr_pcalloc(r->pool, sizeof(cache_object_t));
    dobj = apr_pcalloc(r->pool, sizeof(disk_cache_object_t));

    info = &(obj->info);

    /* Open the headers file */
    dobj->prefix = NULL;

    /* Save the cache root */
    dobj->root = apr_pstrmemdup(r->pool, conf->cache_root, conf->cache_root_len);
    dobj->root_len = conf->cache_root_len;

    dobj->vary.file = header_file(r->pool, conf, dobj, key);
    flags = APR_READ|APR_BINARY|APR_BUFFERED;
    rc = apr_file_open(&dobj->vary.fd, dobj->vary.file, flags, 0, r->pool);
    if (rc != APR_SUCCESS) {
        return DECLINED;
    }

    /* read the format from the cache file */
    len = sizeof(format);
    apr_file_read_full(dobj->vary.fd, &format, len, &len);

    if (format == VARY_FORMAT_VERSION) {
        apr_array_header_t* varray;
        apr_time_t expire;

        len = sizeof(expire);
        apr_file_read_full(dobj->vary.fd, &expire, len, &len);

        varray = apr_array_make(r->pool, 5, sizeof(char*));
        rc = read_array(r, varray, dobj->vary.fd);
        if (rc != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(00704)
                    "Cannot parse vary header file: %s",
                    dobj->vary.file);
            apr_file_close(dobj->vary.fd);
            return DECLINED;
        }
        apr_file_close(dobj->vary.fd);

        nkey = regen_key(r->pool, r->headers_in, varray, key);

        dobj->hashfile = NULL;
        dobj->prefix = dobj->vary.file;
        dobj->hdrs.file = header_file(r->pool, conf, dobj, nkey);

        flags = APR_READ|APR_BINARY|APR_BUFFERED;
        rc = apr_file_open(&dobj->hdrs.fd, dobj->hdrs.file, flags, 0, r->pool);
        if (rc != APR_SUCCESS) {
            return DECLINED;
        }
    }
    else if (format != DISK_FORMAT_VERSION) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00705)
                "File '%s' has a version mismatch. File had version: %d.",
                dobj->vary.file, format);
        apr_file_close(dobj->vary.fd);
        return DECLINED;
    }
    else {
        apr_off_t offset = 0;

        /* oops, not vary as it turns out */
        dobj->hdrs.fd = dobj->vary.fd;
        dobj->vary.fd = NULL;
        dobj->hdrs.file = dobj->vary.file;

        /* This wasn't a Vary Format file, so we must seek to the
         * start of the file again, so that later reads work.
         */
        apr_file_seek(dobj->hdrs.fd, APR_SET, &offset);
        nkey = key;
    }

    obj->key = nkey;
    dobj->key = nkey;
    dobj->name = key;

    apr_pool_create(&pool, r->pool);
    apr_pool_tag(pool, "mod_cache (open_entity)");

    file_cache_create(conf, &dobj->hdrs, pool);
    file_cache_create(conf, &dobj->vary, pool);
    file_cache_create(conf, &dobj->data, pool);

    dobj->data.file = data_file(r->pool, conf, dobj, nkey);

    /* Read the bytes to setup the cache_info fields */
    rc = file_cache_recall_mydata(dobj->hdrs.fd, info, dobj, r);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(00706)
                "Cannot read header file %s", dobj->hdrs.file);
        apr_file_close(dobj->hdrs.fd);
        return DECLINED;
    }


    /* Is this a cached HEAD request? */
    if (dobj->disk_info.header_only && !r->header_only) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00707)
                "HEAD request cached, non-HEAD requested, ignoring: %s",
                dobj->hdrs.file);
        apr_file_close(dobj->hdrs.fd);
        return DECLINED;
    }

    /* Open the data file */
    if (dobj->disk_info.has_body) {
        flags = APR_READ | APR_BINARY;
#ifdef APR_SENDFILE_ENABLED
        /* When we are in the quick handler we don't have the per-directory
         * configuration, so this check only takes the global setting of
         * the EnableSendFile directive into account.
         */
        flags |= AP_SENDFILE_ENABLED(coreconf->enable_sendfile);
#endif
        rc = apr_file_open(&dobj->data.fd, dobj->data.file, flags, 0, r->pool);
        if (rc != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(00708)
                    "Cannot open data file %s", dobj->data.file);
            apr_file_close(dobj->hdrs.fd);
            return DECLINED;
        }

        rc = apr_file_info_get(&finfo, APR_FINFO_SIZE | APR_FINFO_IDENT,
                dobj->data.fd);
        if (rc == APR_SUCCESS) {
            dobj->file_size = finfo.size;
        }

        /* Atomic check - does the body file belong to the header file? */
        if (dobj->disk_info.inode == finfo.inode &&
                dobj->disk_info.device == finfo.device) {

            /* Initialize the cache_handle callback functions */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00709)
                    "Recalled cached URL info header %s", dobj->name);

            /* make the configuration stick */
            h->cache_obj = obj;
            obj->vobj = dobj;

            return OK;
        }

    }
    else {

        /* make the configuration stick */
        h->cache_obj = obj;
        obj->vobj = dobj;

        return OK;
    }

    /* Oh dear, no luck matching header to the body */
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00710)
            "Cached URL info header '%s' didn't match body, ignoring this entry",
            dobj->name);

    apr_file_close(dobj->hdrs.fd);
    return DECLINED;
}