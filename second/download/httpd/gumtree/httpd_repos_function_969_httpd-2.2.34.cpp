static apr_status_t store_headers(cache_handle_t *h, request_rec *r, cache_info *info)
{
    cache_object_t *obj = h->cache_obj;
    mem_cache_object_t *mobj = (mem_cache_object_t*) obj->vobj;
    apr_table_t *headers_out;

    /*
     * The cache needs to keep track of the following information:
     * - Date, LastMod, Version, ReqTime, RespTime, ContentLength
     * - The original request headers (for Vary)
     * - The original response headers (for returning with a cached response)
     * - The body of the message
     */
    if (mobj->lock) {
        apr_thread_mutex_lock(mobj->lock);
    }
    mobj->req_hdrs = deep_table_copy(mobj->pool, r->headers_in);
    if (mobj->lock) {
        apr_thread_mutex_unlock(mobj->lock);
    }

    /* Precompute how much storage we need to hold the headers */
    headers_out = apr_table_overlay(r->pool, r->headers_out,
                                    r->err_headers_out);
    headers_out = ap_cache_cacheable_hdrs_out(r->pool, headers_out,
                                              r->server);

    /* If not set in headers_out, set Content-Type */
    if (!apr_table_get(headers_out, "Content-Type")
        && r->content_type) {
        apr_table_setn(headers_out, "Content-Type",
                       ap_make_content_type(r, r->content_type));
    }

    if (!apr_table_get(headers_out, "Content-Encoding")
        && r->content_encoding) {
        apr_table_setn(headers_out, "Content-Encoding",
                       r->content_encoding);
    }

    if (mobj->lock) {
        apr_thread_mutex_lock(mobj->lock);
    }
    mobj->header_out = deep_table_copy(mobj->pool, headers_out);
    if (mobj->lock) {
        apr_thread_mutex_unlock(mobj->lock);
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