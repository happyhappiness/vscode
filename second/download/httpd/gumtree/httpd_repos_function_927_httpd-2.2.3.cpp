static apr_status_t store_headers(cache_handle_t *h, request_rec *r, cache_info *info)
{
    cache_object_t *obj = h->cache_obj;
    mem_cache_object_t *mobj = (mem_cache_object_t*) obj->vobj;
    int rc;
    apr_table_t *headers_out;

    /*
     * The cache needs to keep track of the following information:
     * - Date, LastMod, Version, ReqTime, RespTime, ContentLength
     * - The original request headers (for Vary)
     * - The original response headers (for returning with a cached response)
     * - The body of the message
     */
    rc = serialize_table(&mobj->req_hdrs,
                         &mobj->num_req_hdrs,
                         r->headers_in);
    if (rc != APR_SUCCESS) {
        return rc;
    }

    /* Precompute how much storage we need to hold the headers */
    headers_out = ap_cache_cacheable_hdrs_out(r->pool, r->headers_out,
                                              r->server);

    /* If not set in headers_out, set Content-Type */
    if (!apr_table_get(headers_out, "Content-Type")
        && r->content_type) {
        apr_table_setn(headers_out, "Content-Type",
                       ap_make_content_type(r, r->content_type));
    }

    headers_out = apr_table_overlay(r->pool, headers_out, r->err_headers_out);

    rc = serialize_table(&mobj->header_out, &mobj->num_header_out,
                         headers_out);
    if (rc != APR_SUCCESS) {
        return rc;
    }

    /* Init the info struct */
    obj->info.status = info->status;
    if (info->date) {
        obj->info.date = info->date;
    }
    if (info->response_time) {
        obj->info.response_time = info->response_time;
    }
    if (info->request_time) {
        obj->info.request_time = info->request_time;
    }
    if (info->expire) {
        obj->info.expire = info->expire;
    }

    return APR_SUCCESS;
}