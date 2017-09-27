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
