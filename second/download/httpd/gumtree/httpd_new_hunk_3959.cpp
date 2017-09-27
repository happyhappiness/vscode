{
    cache_socache_conf *conf = ap_get_module_config(r->server->module_config,
            &cache_socache_module);
    cache_object_t *obj = h->cache_obj;
    cache_socache_object_t *sobj = (cache_socache_object_t *) obj->vobj;
    apr_status_t rv;

    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_lock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02384)
                    "could not acquire lock, ignoring: %s", obj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return status;
        }
    }
    rv = conf->provider->socache_provider->store(
            conf->provider->socache_instance, r->server,
            (unsigned char *) sobj->key, strlen(sobj->key), sobj->expire,
            sobj->buffer, sobj->body_offset + sobj->body_length, sobj->pool);
    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_unlock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02385)
                    "could not release lock, ignoring: %s", obj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return status;
        }
    }
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, r, APLOGNO(02386)
                "could not write to cache, ignoring: %s", sobj->key);
        goto fail;
