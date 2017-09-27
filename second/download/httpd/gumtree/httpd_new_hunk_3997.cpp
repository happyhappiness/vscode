            apr_brigade_destroy(bb);
            return HTTP_MOVED_TEMPORARILY;
        }

        rv = ap_pass_brigade(r->output_filters, bb);
        if (rv != APR_SUCCESS) { 
            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, rv, r,
                          "Failed to flush CGI output to client");
        }
    }

    if (nph) {
        conn_rec *c = r->connection;
        struct ap_filter_t *cur;
