
    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02028)
                  "upgrading connection to TLS");

    bb = apr_brigade_create(r->pool, conn->bucket_alloc);

    rv = ap_fputs(conn->output_filters, bb, SWITCH_STATUS_LINE CRLF
                  UPGRADE_HEADER CRLF CONNECTION_HEADER CRLF CRLF);
    if (rv == APR_SUCCESS) {
        APR_BRIGADE_INSERT_TAIL(bb,
                                apr_bucket_flush_create(conn->bucket_alloc));
        rv = ap_pass_brigade(conn->output_filters, bb);
    }

