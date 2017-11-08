h2_request *h2_request_create(int id, apr_pool_t *pool,
                              const struct h2_config *config)
{
    return h2_request_createn(id, pool, config, 
                              NULL, NULL, NULL, NULL, NULL);
}