static int post_config(apr_pool_t *p,
                       apr_pool_t *plog,
                       apr_pool_t *ptemp,
                       server_rec *s)
{
    apr_status_t rv;
    void *data;
    int first_time = 0;
    const char *userdata_key = "rewrite_init_module";

    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
    if (!data) {
        first_time = 1;
        apr_pool_userdata_set((const void *)1, userdata_key,
                              apr_pool_cleanup_null, s->process->pool);
    }

    /* check if proxy module is available */
    proxy_available = (ap_find_linked_module("mod_proxy.c") != NULL);

    rv = rewritelock_create(s, p);
    if (rv != APR_SUCCESS) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    apr_pool_cleanup_register(p, (void *)s, rewritelock_remove,
                              apr_pool_cleanup_null);

    /* step through the servers and
     * - open each rewriting logfile
     * - open the RewriteMap prg:xxx programs
     */
    for (; s; s = s->next) {
#ifndef REWRITELOG_DISABLED
        if (!open_rewritelog(s, p)) {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
#endif

        if (!first_time) {
            if (run_rewritemap_programs(s, p) != APR_SUCCESS) {
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
    }

    rewrite_ssl_lookup = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
    rewrite_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);

    return OK;
}