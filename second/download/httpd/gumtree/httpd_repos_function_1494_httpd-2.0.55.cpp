static int create_fd_entity(cache_handle_t *h, request_rec *r,
                            const char *key, apr_off_t len) 
{
    return create_entity(h, CACHE_TYPE_FILE, r, key, len);
}