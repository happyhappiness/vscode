                         "handle request");

            /* We are in the quick handler hook, which means that no output
             * filters have been set. So lets run the insert_filter hook.
             */
            ap_run_insert_filter(r);
            ap_add_output_filter("CACHE_OUT", NULL, r, r->connection);

            /* kick off the filter stack */
            out = apr_brigade_create(r->pool, c->bucket_alloc);
            if (APR_SUCCESS
                != (rv = ap_pass_brigade(r->output_filters, out))) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
