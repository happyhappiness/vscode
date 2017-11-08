static apr_status_t invalidate_entity(cache_handle_t *h, request_rec *r)
{
    apr_status_t rv;

    rv = recall_headers(h, r);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* mark the entity as invalidated */
    h->cache_obj->info.control.invalidated = 1;

    return commit_entity(h, r);
}