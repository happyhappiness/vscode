static int create_mem_entity(cache_handle_t *h, request_rec *r,
                             const char *key, apr_off_t len) 
{
    return create_entity(h, CACHE_TYPE_HEAP, r, key, len);
}