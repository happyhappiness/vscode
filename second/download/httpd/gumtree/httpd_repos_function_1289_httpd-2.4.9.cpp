static int open_entity(cache_handle_t *h, request_rec *r, const char *key)
{
    cache_socache_dir_conf *dconf =
            ap_get_module_config(r->per_dir_config, &cache_socache_module);
    cache_socache_conf *conf = ap_get_module_config(r->server->module_config,
            &cache_socache_module);
    apr_uint32_t format;
    apr_size_t slider;
    unsigned int buffer_len;
    const char *nkey;
    apr_status_t rc;
    cache_object_t *obj;
    cache_info *info;
    cache_socache_object_t *sobj;
    apr_size_t len;

    nkey = NULL;
    h->cache_obj = NULL;

    if (!conf->provider || !conf->provider->socache_instance) {
        return DECLINED;
    }

    /* Create and init the cache object */
    obj = apr_pcalloc(r->pool, sizeof(cache_object_t));
    sobj = apr_pcalloc(r->pool, sizeof(cache_socache_object_t));

    info = &(obj->info);

    /* Create a temporary pool for the buffer, and destroy it if something
     * goes wrong so we don't have large buffers of unused memory hanging
     * about for the lifetime of the response.
     */
    apr_pool_create(&sobj->pool, r->pool);

    sobj->buffer = apr_palloc(sobj->pool, dconf->max + 1);
    sobj->buffer_len = dconf->max + 1;

    /* attempt to retrieve the cached entry */
    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_lock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02350)
                    "could not acquire lock, ignoring: %s", obj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return DECLINED;
        }
    }
    buffer_len = sobj->buffer_len;
    rc = conf->provider->socache_provider->retrieve(
            conf->provider->socache_instance, r->server, (unsigned char *) key,
            strlen(key), sobj->buffer, &buffer_len, r->pool);
    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_unlock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02351)
                    "could not release lock, ignoring: %s", obj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return DECLINED;
        }
    }
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rc, r, APLOGNO(02352)
                "Key not found in cache: %s", key);
        apr_pool_destroy(sobj->pool);
        sobj->pool = NULL;
        return DECLINED;
    }
    if (buffer_len >= sobj->buffer_len) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rc, r, APLOGNO(02353)
                "Key found in cache but too big, ignoring: %s", key);
        apr_pool_destroy(sobj->pool);
        sobj->pool = NULL;
        return DECLINED;
    }

    /* read the format from the cache file */
    memcpy(&format, sobj->buffer, sizeof(format));
    slider = sizeof(format);

    if (format == CACHE_SOCACHE_VARY_FORMAT_VERSION) {
        apr_array_header_t* varray;
        apr_time_t expire;

        memcpy(&expire, sobj->buffer + slider, sizeof(expire));
        slider += sizeof(expire);

        varray = apr_array_make(r->pool, 5, sizeof(char*));
        rc = read_array(r, varray, sobj->buffer, buffer_len, &slider);
        if (rc != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(02354)
                    "Cannot parse vary entry for key: %s", key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return DECLINED;
        }

        nkey = regen_key(r->pool, r->headers_in, varray, key);

        /* attempt to retrieve the cached entry */
        if (socache_mutex) {
            apr_status_t status = apr_global_mutex_lock(socache_mutex);
            if (status != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02355)
                        "could not acquire lock, ignoring: %s", obj->key);
                apr_pool_destroy(sobj->pool);
                sobj->pool = NULL;
                return DECLINED;
            }
        }
        buffer_len = sobj->buffer_len;
        rc = conf->provider->socache_provider->retrieve(
                conf->provider->socache_instance, r->server,
                (unsigned char *) nkey, strlen(nkey), sobj->buffer,
                &buffer_len, r->pool);
        if (socache_mutex) {
            apr_status_t status = apr_global_mutex_unlock(socache_mutex);
            if (status != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02356)
                        "could not release lock, ignoring: %s", obj->key);
                apr_pool_destroy(sobj->pool);
                sobj->pool = NULL;
                return DECLINED;
            }
        }
        if (rc != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rc, r, APLOGNO(02357)
                    "Key not found in cache: %s", key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return DECLINED;
        }
        if (buffer_len >= sobj->buffer_len) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rc, r, APLOGNO(02358)
                    "Key found in cache but too big, ignoring: %s", key);
            goto fail;
        }

    }
    else if (format != CACHE_SOCACHE_DISK_FORMAT_VERSION) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02359)
                "Key '%s' found in cache has version %d, expected %d, ignoring",
                key, format, CACHE_SOCACHE_DISK_FORMAT_VERSION);
        goto fail;
    }
    else {
        nkey = key;
    }

    obj->key = nkey;
    sobj->key = nkey;
    sobj->name = key;

    if (buffer_len >= sizeof(cache_socache_info_t)) {
        memcpy(&sobj->socache_info, sobj->buffer, sizeof(cache_socache_info_t));
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(02360)
                "Cache entry for key '%s' too short, removing", nkey);
        goto fail;
    }
    slider = sizeof(cache_socache_info_t);

    /* Store it away so we can get it later. */
    info->status = sobj->socache_info.status;
    info->date = sobj->socache_info.date;
    info->expire = sobj->socache_info.expire;
    info->request_time = sobj->socache_info.request_time;
    info->response_time = sobj->socache_info.response_time;

    memcpy(&info->control, &sobj->socache_info.control, sizeof(cache_control_t));

    if (sobj->socache_info.name_len <= buffer_len - slider) {
        if (strncmp((const char *) sobj->buffer + slider, sobj->name,
                sobj->socache_info.name_len)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(02361)
                    "Cache entry for key '%s' URL mismatch, ignoring", nkey);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return DECLINED;
        }
        slider += sobj->socache_info.name_len;
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(02362)
                "Cache entry for key '%s' too short, removing", nkey);
        goto fail;
    }

    /* Is this a cached HEAD request? */
    if (sobj->socache_info.header_only && !r->header_only) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(02363)
                "HEAD request cached, non-HEAD requested, ignoring: %s",
                sobj->key);
        apr_pool_destroy(sobj->pool);
        sobj->pool = NULL;
        return DECLINED;
    }

    h->req_hdrs = apr_table_make(r->pool, 20);
    h->resp_hdrs = apr_table_make(r->pool, 20);

    /* Call routine to read the header lines/status line */
    if (APR_SUCCESS != read_table(h, r, h->resp_hdrs, sobj->buffer, buffer_len,
            &slider)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(02364)
                "Cache entry for key '%s' response headers unreadable, removing", nkey);
        goto fail;
    }
    if (APR_SUCCESS != read_table(h, r, h->req_hdrs, sobj->buffer, buffer_len,
            &slider)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(02365)
                "Cache entry for key '%s' request headers unreadable, removing", nkey);
        goto fail;
    }

    /* Retrieve the body if we have one */
    sobj->body = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    len = buffer_len - slider;

    /*
     *  Optimisation: if the body is small, we want to make a
     *  copy of the body and free the temporary pool, as we
     *  don't want large blocks of unused memory hanging around
     *  to the end of the response. In contrast, if the body is
     *  large, we would rather leave the body where it is in the
     *  temporary pool, and save ourselves the copy.
     */
    if (len * 2 > dconf->max) {
        apr_bucket *e;

        /* large - use the brigade as is, we're done */
        e = apr_bucket_immortal_create((const char *) sobj->buffer + slider,
                len, r->connection->bucket_alloc);

        APR_BRIGADE_INSERT_TAIL(sobj->body, e);
    }
    else {

        /* small - make a copy of the data... */
        apr_brigade_write(sobj->body, NULL, NULL, (const char *) sobj->buffer
                + slider, len);

        /* ...and get rid of the large memory buffer */
        apr_pool_destroy(sobj->pool);
        sobj->pool = NULL;
    }

    /* make the configuration stick */
    h->cache_obj = obj;
    obj->vobj = sobj;

    return OK;

fail:
    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_lock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02366)
                    "could not acquire lock, ignoring: %s", obj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return DECLINED;
        }
    }
    conf->provider->socache_provider->remove(
            conf->provider->socache_instance, r->server,
            (unsigned char *) nkey, strlen(nkey), r->pool);
    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_unlock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02367)
                    "could not release lock, ignoring: %s", obj->key);
        }
    }
    apr_pool_destroy(sobj->pool);
    sobj->pool = NULL;
    return DECLINED;
}