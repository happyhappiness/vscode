             */
            discard_script_output(bb);
            apr_brigade_destroy(bb);
            return HTTP_MOVED_TEMPORARILY;
        }

        rv = ap_pass_brigade(r->output_filters, bb);
        if (rv != APR_SUCCESS) { 
            /* APLOG_ERR because the core output filter message is at error,
             * but doesn't know it's passing CGI output 
             */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02550) "Failed to flush CGI output to client");
        }
    }

    if (nph) {
        conn_rec *c = r->connection;
        struct ap_filter_t *cur;

