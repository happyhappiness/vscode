        return NULL;
}

static int proxy_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t rv = ap_global_mutex_create(&proxy_mutex, NULL,
            proxy_id, NULL, s, pconf, 0);
    if (rv != APR_SUCCESS) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(02478)
        "failed to create %s mutex", proxy_id);
        return rv;
    }

    proxy_ssl_enable = APR_RETRIEVE_OPTIONAL_FN(ssl_proxy_enable);
    proxy_ssl_disable = APR_RETRIEVE_OPTIONAL_FN(ssl_engine_disable);
    proxy_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
    proxy_ssl_val = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
    ap_proxy_strmatch_path = apr_strmatch_precompile(pconf, "path=", 0);
