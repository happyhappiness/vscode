{
    cache_socache_conf *conf = ap_get_module_config(r->server->module_config,
            &cache_socache_module);
    cache_object_t *obj = h->cache_obj;
    cache_socache_object_t *sobj = (cache_socache_object_t *) obj->vobj;
    apr_status_t rv;
    apr_size_t len;

    /* flatten the body into the buffer */
    len = sobj->buffer_len - sobj->body_offset;
    rv = apr_brigade_flatten(sobj->body, (char *) sobj->buffer
            + sobj->body_offset, &len);
    if (APR_SUCCESS != rv) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02382)
                "could not flatten brigade, not caching: %s",
                sobj->key);
        goto fail;
    }
    if (len >= sobj->buffer_len - sobj->body_offset) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02383)
                "body too big for the cache buffer, not caching: %s",
                h->cache_obj->key);
        goto fail;
    }

    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_lock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02384)
                    "could not acquire lock, ignoring: %s", obj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return rv;
        }
    }
    rv = conf->provider->socache_provider->store(
            conf->provider->socache_instance, r->server,
            (unsigned char *) sobj->key, strlen(sobj->key), sobj->expire,
            sobj->buffer, (unsigned int) sobj->body_offset + len, sobj->pool);
    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_unlock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02385)
                    "could not release lock, ignoring: %s", obj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return DECLINED;
        }
    }
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(02386)
                "could not write to cache, ignoring: %s", sobj->key);
        goto fail;
