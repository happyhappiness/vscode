static apr_status_t commit_entity(cache_handle_t *h, request_rec *r)
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
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02387)
            "commit_entity: Headers and body for URL %s cached for maximum of %d seconds.",
            sobj->name, (apr_uint32_t)apr_time_sec(sobj->expire - r->request_time));

    apr_pool_destroy(sobj->pool);
    sobj->pool = NULL;

    return APR_SUCCESS;

fail:
    /* For safety, remove any existing entry on failure, just in case it could not
     * be revalidated successfully.
     */
    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_lock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02388)
                    "could not acquire lock, ignoring: %s", obj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return rv;
        }
    }
    conf->provider->socache_provider->remove(conf->provider->socache_instance,
            r->server, (unsigned char *) sobj->key, strlen(sobj->key), r->pool);
    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_unlock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02389)
                    "could not release lock, ignoring: %s", obj->key);
        }
    }

    apr_pool_destroy(sobj->pool);
    sobj->pool = NULL;
    return rv;
}