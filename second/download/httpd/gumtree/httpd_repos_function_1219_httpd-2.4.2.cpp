static apr_status_t store_headers(cache_handle_t *h, request_rec *r, cache_info *info)
{
    disk_cache_object_t *dobj = (disk_cache_object_t*) h->cache_obj->vobj;

    memcpy(&h->cache_obj->info, info, sizeof(cache_info));

    if (r->headers_out) {
        dobj->headers_out = ap_cache_cacheable_headers_out(r);
    }

    if (r->headers_in) {
        dobj->headers_in = ap_cache_cacheable_headers_in(r);
    }

    return APR_SUCCESS;
}