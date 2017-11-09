h2_headers *h2_headers_copy(apr_pool_t *pool, h2_headers *h)
{
    return h2_headers_create(h->status, apr_table_copy(pool, h->headers), 
                             apr_table_copy(pool, h->notes), pool);
}