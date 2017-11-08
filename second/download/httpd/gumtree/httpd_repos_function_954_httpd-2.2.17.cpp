static apr_status_t recall_headers(cache_handle_t *h, request_rec *r)
{
    mem_cache_object_t *mobj = (mem_cache_object_t*) h->cache_obj->vobj;

    h->req_hdrs = deep_table_copy(r->pool, mobj->req_hdrs);
    h->resp_hdrs = deep_table_copy(r->pool, mobj->header_out);

    return OK;
}