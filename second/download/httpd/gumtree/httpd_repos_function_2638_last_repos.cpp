h2_proxy_request *h2_proxy_req_create(int id, apr_pool_t *pool, int serialize)
{
    return h2_proxy_req_createn(id, pool, NULL, NULL, NULL, NULL, NULL, serialize);
}