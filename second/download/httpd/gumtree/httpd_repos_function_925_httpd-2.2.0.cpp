static apr_status_t recall_headers(cache_handle_t *h, request_rec *r)
{
    int rc;
    mem_cache_object_t *mobj = (mem_cache_object_t*) h->cache_obj->vobj;

    h->req_hdrs = apr_table_make(r->pool, mobj->num_req_hdrs);
    h->resp_hdrs = apr_table_make(r->pool, mobj->num_header_out);

    rc = unserialize_table(mobj->req_hdrs, mobj->num_req_hdrs, h->req_hdrs);
    rc = unserialize_table(mobj->header_out, mobj->num_header_out,
                           h->resp_hdrs);

    return rc;
}