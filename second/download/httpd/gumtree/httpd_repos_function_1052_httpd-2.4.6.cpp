static int lua_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{
    lua_ssl_val = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
    lua_ssl_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
    return OK;
}