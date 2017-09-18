             */
            ap_run_insert_filter(r);
            ap_add_output_filter("CACHE_OUT", NULL, r, r->connection);

            /* kick off the filter stack */
            out = apr_brigade_create(r->pool, c->bucket_alloc);
            if (APR_SUCCESS
                != (rv = ap_pass_brigade(r->output_filters, out))) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                             "cache: error returned while trying to return %s "
                             "cached data", 
                             cache->type);
                return rv;
            }
