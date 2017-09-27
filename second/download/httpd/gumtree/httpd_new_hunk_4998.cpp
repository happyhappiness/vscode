        if (status != OK)
            backend->close = 1;
        ap_proxy_http_cleanup(proxy_function, r, backend);
    }
    return status;
}

/* post_config hook: */
static int proxy_http_post_config(apr_pool_t *pconf, apr_pool_t *plog,
        apr_pool_t *ptemp, server_rec *s)
{

    /* proxy_http_post_config() will be called twice during startup.  So, don't
     * set up the static data the 1st time through. */
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
        return OK;
    }

    if (!ap_proxy_clear_connection_fn) {
        ap_proxy_clear_connection_fn =
                APR_RETRIEVE_OPTIONAL_FN(ap_proxy_clear_connection);
        if (!ap_proxy_clear_connection_fn) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02477)
                         "mod_proxy must be loaded for mod_proxy_http");
            return !OK;
        }
    }

    return OK;
}

static void ap_proxy_http_register_hook(apr_pool_t *p)
{
    ap_hook_post_config(proxy_http_post_config, NULL, NULL, APR_HOOK_MIDDLE);
    proxy_hook_scheme_handler(proxy_http_handler, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_canon_handler(proxy_http_canon, NULL, NULL, APR_HOOK_FIRST);
    warn_rx = ap_pregcomp(p, "[0-9]{3}[ \t]+[^ \t]+[ \t]+\"[^\"]*\"([ \t]+\"([^\"]+)\")?", 0);
}

AP_DECLARE_MODULE(proxy_http) = {
