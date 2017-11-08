static int remove_url(cache_handle_t *h, request_rec *r)
{
    cache_socache_conf *conf = ap_get_module_config(r->server->module_config,
            &cache_socache_module);
    cache_socache_object_t *sobj;

    sobj = (cache_socache_object_t *) h->cache_obj->vobj;
    if (!sobj) {
        return DECLINED;
    }

    /* Remove the key from the cache */
    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_lock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02368)
                    "could not acquire lock, ignoring: %s", sobj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return DECLINED;
        }
    }
    conf->provider->socache_provider->remove(conf->provider->socache_instance,
            r->server, (unsigned char *) sobj->key, strlen(sobj->key), r->pool);
    if (socache_mutex) {
        apr_status_t status = apr_global_mutex_unlock(socache_mutex);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02369)
                    "could not release lock, ignoring: %s", sobj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return DECLINED;
        }
    }

    return OK;
}