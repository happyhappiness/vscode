static apr_status_t recall_headers(cache_handle_t *h, request_rec *r)
{
    disk_cache_object_t *dobj = (disk_cache_object_t *) h->cache_obj->vobj;

    /* This case should not happen... */
    if (!dobj->hfd) {
        /* XXX log message */
        return APR_NOTFOUND;
    }

    h->req_hdrs = apr_table_make(r->pool, 20);
    h->resp_hdrs = apr_table_make(r->pool, 20);

