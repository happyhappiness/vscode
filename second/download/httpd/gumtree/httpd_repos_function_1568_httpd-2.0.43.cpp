int cache_remove_entity(request_rec *r, const char *types, cache_handle_t *h)
{
    h->remove_entity(h);
    return 1;
}