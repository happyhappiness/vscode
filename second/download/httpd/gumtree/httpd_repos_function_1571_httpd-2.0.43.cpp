apr_status_t cache_write_entity_body(cache_handle_t *h, request_rec *r, apr_bucket_brigade *b) 
{
    return (h->write_body(h, r, b));
}