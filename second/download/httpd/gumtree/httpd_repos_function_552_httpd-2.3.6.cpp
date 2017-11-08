static int setenvif_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                                apr_pool_t *ptemp, server_rec *s)
{
    ssl_ext_list_func = APR_RETRIEVE_OPTIONAL_FN(ssl_ext_list);
    return OK;
}