static int create_entity(cache_handle_t *h, request_rec *r, const char *key, apr_off_t len,
                         apr_bucket_brigade *bb)
{
    disk_cache_dir_conf *dconf = ap_get_module_config(r->per_dir_config, &cache_disk_module);
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &cache_disk_module);
    cache_object_t *obj;
    disk_cache_object_t *dobj;
    apr_pool_t *pool;

    if (conf->cache_root == NULL) {
        return DECLINED;
    }

    /* we don't support caching of range requests (yet) */
    if (r->status == HTTP_PARTIAL_CONTENT) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00700)
                "URL %s partial content response not cached",
                key);
        return DECLINED;
    }

    /* Note, len is -1 if unknown so don't trust it too hard */
    if (len > dconf->maxfs) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00701)
                "URL %s failed the size check "
                "(%" APR_OFF_T_FMT " > %" APR_OFF_T_FMT ")",
                key, len, dconf->maxfs);
        return DECLINED;
    }
    if (len >= 0 && len < dconf->minfs) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00702)
                "URL %s failed the size check "
                "(%" APR_OFF_T_FMT " < %" APR_OFF_T_FMT ")",
                key, len, dconf->minfs);
        return DECLINED;
    }

    /* Allocate and initialize cache_object_t and disk_cache_object_t */
    h->cache_obj = obj = apr_pcalloc(r->pool, sizeof(*obj));
    obj->vobj = dobj = apr_pcalloc(r->pool, sizeof(*dobj));

    obj->key = apr_pstrdup(r->pool, key);

    dobj->name = obj->key;
    dobj->prefix = NULL;
    /* Save the cache root */
    dobj->root = apr_pstrmemdup(r->pool, conf->cache_root, conf->cache_root_len);
    dobj->root_len = conf->cache_root_len;

    apr_pool_create(&pool, r->pool);
    apr_pool_tag(pool, "mod_cache (create_entity)");

    file_cache_create(conf, &dobj->hdrs, pool);
    file_cache_create(conf, &dobj->vary, pool);
    file_cache_create(conf, &dobj->data, pool);

    dobj->data.file = data_file(r->pool, conf, dobj, key);
    dobj->hdrs.file = header_file(r->pool, conf, dobj, key);
    dobj->vary.file = header_file(r->pool, conf, dobj, key);

    dobj->disk_info.header_only = r->header_only;

    return OK;
}