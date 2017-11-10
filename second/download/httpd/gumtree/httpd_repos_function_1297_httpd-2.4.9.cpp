static apr_status_t invalidate_entity(cache_handle_t *h, request_rec *r)
{
    /* mark the entity as invalidated */
    h->cache_obj->info.control.invalidated = 1;

    return commit_entity(h, r);
}