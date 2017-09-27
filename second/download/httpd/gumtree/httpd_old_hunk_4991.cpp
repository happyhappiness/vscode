        return NULL;
}

static int proxy_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{

    proxy_ssl_enable = APR_RETRIEVE_OPTIONAL_FN(ssl_proxy_enable);
    proxy_ssl_disable = APR_RETRIEVE_OPTIONAL_FN(ssl_engine_disable);
    proxy_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
    proxy_ssl_val = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
    ap_proxy_strmatch_path = apr_strmatch_precompile(pconf, "path=", 0);
