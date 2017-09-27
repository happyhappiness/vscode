                                        MC_DEFAULT_SERVER_MIN,
                                        MC_DEFAULT_SERVER_SMAX,
                                        thread_limit,
                                        MC_DEFAULT_SERVER_TTL,
                                        &st);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                         "socache: Failed to Create memcache Server: %s:%d", 
                         host_str, port);
            return rv;
        }

        rv = apr_memcache_add_server(ctx->mc, st);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                         "socache: Failed to Add memcache Server: %s:%d", 
                         host_str, port);
            return rv;
        }

        split = apr_strtok(NULL,",", &tok);
    }
