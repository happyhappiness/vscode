static int header_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                              apr_pool_t *ptemp, server_rec *s)
{
    header_ssl_lookup = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
    return OK;
}