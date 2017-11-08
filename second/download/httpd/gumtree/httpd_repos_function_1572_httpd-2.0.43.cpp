apr_status_t cache_read_entity_headers(cache_handle_t *h, request_rec *r)
{
    apr_status_t rv;
    cache_info *info = &(h->cache_obj->info);

    /* Build the header table from info in the info struct */
    rv = h->read_headers(h, r);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    r->filename = apr_pstrdup(r->pool, info->filename );

    return APR_SUCCESS;
}