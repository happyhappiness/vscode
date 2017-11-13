static int create_entity(cache_handle_t *h, request_rec *r, const char *key, apr_off_t len)
{
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &disk_cache_module);
    cache_object_t *obj;
    disk_cache_object_t *dobj;

    if (conf->cache_root == NULL) {
        return DECLINED;
    }

    /* we don't support caching of range requests (yet) */
    if (r->status == HTTP_PARTIAL_CONTENT) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "disk_cache: URL %s partial content response not cached",
                     key);
        return DECLINED;
    }

    /* Note, len is -1 if unknown so don't trust it too hard */
    if (len > conf->maxfs) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "disk_cache: URL %s failed the size check "
                     "(%" APR_OFF_T_FMT " > %" APR_OFF_T_FMT ")",
                     key, len, conf->maxfs);
        return DECLINED;
    }
    if (len >= 0 && len < conf->minfs) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "disk_cache: URL %s failed the size check "
                     "(%" APR_OFF_T_FMT " < %" APR_OFF_T_FMT ")",
                     key, len, conf->minfs);
        return DECLINED;
    }

    /* Allocate and initialize cache_object_t and disk_cache_object_t */
    h->cache_obj = obj = apr_pcalloc(r->pool, sizeof(*obj));
    obj->vobj = dobj = apr_pcalloc(r->pool, sizeof(*dobj));

    obj->key = apr_pstrdup(r->pool, key);

    dobj->name = obj->key;
    dobj->prefix = NULL;
    /* Save the cache root */
    dobj->root = apr_pstrndup(r->pool, conf->cache_root, conf->cache_root_len);
    dobj->root_len = conf->cache_root_len;
    dobj->datafile = data_file(r->pool, conf, dobj, key);
    dobj->hdrsfile = header_file(r->pool, conf, dobj, key);
    dobj->tempfile = apr_pstrcat(r->pool, conf->cache_root, AP_TEMPFILE, NULL);

    return OK;
}