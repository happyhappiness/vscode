static int ap_expr_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                               apr_pool_t *ptemp, server_rec *s)
{
    is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
    is_http2 = APR_RETRIEVE_OPTIONAL_FN(http2_is_h2);
    apr_pool_cleanup_register(pconf, &is_https, ap_pool_cleanup_set_null,
                              apr_pool_cleanup_null);
    return OK;
}