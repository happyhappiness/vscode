static apr_status_t store_headers(cache_handle_t *h, request_rec *r, cache_info *info)
{
    cache_object_t *obj = h->cache_obj;
    mem_cache_object_t *mobj = (mem_cache_object_t*) obj->vobj;
    int rc;
 
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
    rc = serialize_table(&mobj->header_out, 
                         &mobj->num_header_out, 
                         ap_cache_cacheable_hdrs_out(r->pool, r->headers_out,
                                                     r->server));
    if (rc != APR_SUCCESS) {
        return rc;
    }
    rc = serialize_table(&mobj->err_header_out, 
                         &mobj->num_err_header_out, 
                         ap_cache_cacheable_hdrs_out(r->pool,
                                                     r->err_headers_out,
                                                     r->server));
    if (rc != APR_SUCCESS) {
        return rc;
    }
    rc = serialize_table(&mobj->subprocess_env,
                         &mobj->num_subprocess_env, 
                         r->subprocess_env );
    if (rc != APR_SUCCESS) {
        return rc;
    }

    rc = serialize_table(&mobj->notes, &mobj->num_notes, r->notes);
    if (rc != APR_SUCCESS) {
        return rc;
    }
 
    /* Init the info struct */
    obj->info.status = info->status;
    if (info->date) {
        obj->info.date = info->date;
    }
    if (info->lastmod) {
        obj->info.lastmod = info->lastmod;
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
    if (info->content_type) {
        apr_size_t len = strlen(info->content_type) + 1;
        obj->info.content_type = (char*) malloc(len);
        if (!obj->info.content_type) {
            return APR_ENOMEM;
        }
        memcpy(obj->info.content_type, info->content_type, len);
    }
    if (info->etag) {
        apr_size_t len = strlen(info->etag) + 1;
        obj->info.etag = (char*) malloc(len);
        if (!obj->info.etag) {
            return APR_ENOMEM;
        }
        memcpy(obj->info.etag, info->etag, len);
    }
    if (info->lastmods) {
        apr_size_t len = strlen(info->lastmods) + 1;
        obj->info.lastmods = (char*) malloc(len);
        if (!obj->info.lastmods) {
            return APR_ENOMEM;
        }
        memcpy(obj->info.lastmods, info->lastmods, len);
    }
    if ( info->filename) {
        apr_size_t len = strlen(info->filename) + 1;
        obj->info.filename = (char*) malloc(len);
        if (!obj->info.filename ) {
            return APR_ENOMEM;
        }
        memcpy(obj->info.filename, info->filename, len);
    }

    return APR_SUCCESS;
}