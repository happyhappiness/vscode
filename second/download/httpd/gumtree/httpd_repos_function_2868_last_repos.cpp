h2_headers *h2_headers_create(int status, apr_table_t *headers_in, 
                                apr_table_t *notes, apr_pool_t *pool)
{
    h2_headers *headers = apr_pcalloc(pool, sizeof(h2_headers));
    headers->status    = status;
    headers->headers   = (headers_in? apr_table_copy(pool, headers_in)
                           : apr_table_make(pool, 5));
    headers->notes     = (notes? apr_table_copy(pool, notes)
                           : apr_table_make(pool, 5));
    return headers;
}