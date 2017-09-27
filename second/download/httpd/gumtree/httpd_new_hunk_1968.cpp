    }

    /* kick off the filter stack */
    out = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    rv = ap_pass_brigade(r->output_filters, out);
    if (rv != APR_SUCCESS) {
        if (rv != AP_FILTER_ERROR) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                         "cache: error returned while trying to return %s "
                         "cached data",
                         cache->provider_name);
        }
        return rv;
    }

    return OK;
}

