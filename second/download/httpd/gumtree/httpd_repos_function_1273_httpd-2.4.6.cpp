static apr_status_t socache_mc_init(ap_socache_instance_t *ctx,
                                    const char *namespace,
                                    const struct ap_socache_hints *hints,
                                    server_rec *s, apr_pool_t *p)
{
    apr_status_t rv;
    int thread_limit = 0;
    int nservers = 0;
    char *cache_config;
    char *split;
    char *tok;

    ap_mpm_query(AP_MPMQ_HARD_LIMIT_THREADS, &thread_limit);

    /* Find all the servers in the first run to get a total count */
    cache_config = apr_pstrdup(p, ctx->servers);
    split = apr_strtok(cache_config, ",", &tok);
    while (split) {
        nservers++;
        split = apr_strtok(NULL,",", &tok);
    }

    rv = apr_memcache_create(p, nservers, 0, &ctx->mc);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(00785)
                     "Failed to create Memcache Object of '%d' size.",
                     nservers);
        return rv;
    }

    /* Now add each server to the memcache */
    cache_config = apr_pstrdup(p, ctx->servers);
    split = apr_strtok(cache_config, ",", &tok);
    while (split) {
        apr_memcache_server_t *st;
        char *host_str;
        char *scope_id;
        apr_port_t port;

        rv = apr_parse_addr_port(&host_str, &scope_id, &port, split, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(00786)
                         "Failed to Parse memcache Server: '%s'", split);
            return rv;
        }

        if (host_str == NULL) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(00787)
                         "Failed to Parse Server, "
                         "no hostname specified: '%s'", split);
            return APR_EINVAL;
        }

        if (port == 0) {
            port = MC_DEFAULT_SERVER_PORT;
        }

        rv = apr_memcache_server_create(p,
                                        host_str, port,
                                        MC_DEFAULT_SERVER_MIN,
                                        MC_DEFAULT_SERVER_SMAX,
                                        thread_limit,
                                        MC_DEFAULT_SERVER_TTL,
                                        &st);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(00788)
                         "Failed to Create memcache Server: %s:%d",
                         host_str, port);
            return rv;
        }

        rv = apr_memcache_add_server(ctx->mc, st);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(00789)
                         "Failed to Add memcache Server: %s:%d",
                         host_str, port);
            return rv;
        }

        split = apr_strtok(NULL,",", &tok);
    }

    ctx->tag = apr_pstrcat(p, namespace, ":", NULL);
    ctx->taglen = strlen(ctx->tag) + 1;

    /* socache API constraint: */
    AP_DEBUG_ASSERT(ctx->taglen <= 16);

    return APR_SUCCESS;
}