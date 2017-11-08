static apr_status_t recall_headers(cache_handle_t *h, request_rec *r) 
{
    int rc;
    mem_cache_object_t *mobj = (mem_cache_object_t*) h->cache_obj->vobj;
 
    h->req_hdrs = apr_table_make(r->pool, mobj->num_req_hdrs);
    h->resp_hdrs = apr_table_make(r->pool, mobj->num_header_out);
    h->resp_err_hdrs = apr_table_make(r->pool, mobj->num_err_header_out);
    /* ### FIXME: These two items should not be saved. */
    r->subprocess_env = apr_table_make(r->pool, mobj->num_subprocess_env);
    r->notes = apr_table_make(r->pool, mobj->num_notes);

    rc = unserialize_table(mobj->req_hdrs,
                           mobj->num_req_hdrs,
                           h->req_hdrs);
    rc = unserialize_table( mobj->header_out,
                            mobj->num_header_out, 
                            h->resp_hdrs);
    rc = unserialize_table( mobj->err_header_out,
                            mobj->num_err_header_out, 
                            h->resp_err_hdrs);
    rc = unserialize_table( mobj->subprocess_env, 
                            mobj->num_subprocess_env, 
                            r->subprocess_env);
    rc = unserialize_table( mobj->notes,
                            mobj->num_notes,
                            r->notes);

    /* Content-Type: header may not be set if content is local since
     * CACHE_IN runs before header filters....
     */
    h->content_type = h->cache_obj->info.content_type;
    h->status = h->cache_obj->info.status;

    return rc;
}