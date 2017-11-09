static int mod_deflate_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                                   apr_pool_t *ptemp, server_rec *s)
{
    mod_deflate_ssl_var = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
    return OK;
}