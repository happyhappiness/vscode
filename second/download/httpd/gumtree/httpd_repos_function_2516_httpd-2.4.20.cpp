static apr_status_t add_all_h1_header(h2_request *req, apr_pool_t *pool, 
                                      apr_table_t *header)
{
    h1_ctx x;
    x.req = req;
    x.pool = pool;
    apr_table_do(set_h1_header, &x, header, NULL);
    return APR_SUCCESS;
}