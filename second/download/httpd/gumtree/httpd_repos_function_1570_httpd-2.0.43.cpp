apr_status_t cache_write_entity_headers(cache_handle_t *h, 
                                        request_rec *r, 
                                        cache_info *info)
{
    return (h->write_headers(h, r, info));
}