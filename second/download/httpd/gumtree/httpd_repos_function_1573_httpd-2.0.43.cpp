apr_status_t cache_read_entity_body(cache_handle_t *h, apr_pool_t *p, apr_bucket_brigade *b) 
{
    return (h->read_body(h, p, b));
}