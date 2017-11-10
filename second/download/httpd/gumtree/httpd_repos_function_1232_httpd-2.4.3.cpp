static apr_status_t commit_entity(cache_handle_t *h, request_rec *r)
{
    disk_cache_conf *conf = ap_get_module_config(r->server->module_config,
                                                 &cache_disk_module);
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;
    apr_status_t rv;

    /* write the headers to disk at the last possible moment */
    rv = write_headers(h, r);

    /* move header and data tempfiles to the final destination */
    if (APR_SUCCESS == rv) {
        rv = file_cache_el_final(conf, &dobj->hdrs, r);
    }
    if (APR_SUCCESS == rv) {
        rv = file_cache_el_final(conf, &dobj->vary, r);
    }
    if (APR_SUCCESS == rv) {
        rv = file_cache_el_final(conf, &dobj->data, r);
    }

    /* remove the cached items completely on any failure */
    if (APR_SUCCESS != rv) {
        remove_url(h, r);
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00736)
                "commit_entity: URL '%s' not cached due to earlier disk error.",
                dobj->name);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00737)
                "commit_entity: Headers and body for URL %s cached.",
                dobj->name);
    }

    apr_pool_destroy(dobj->data.pool);

    return APR_SUCCESS;
}