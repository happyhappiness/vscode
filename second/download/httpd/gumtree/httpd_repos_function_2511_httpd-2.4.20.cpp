h2_request *h2_request_create(int id, apr_pool_t *pool, int serialize)
{
    return h2_request_createn(id, pool, NULL, NULL, NULL, NULL, NULL,
                              serialize);
}