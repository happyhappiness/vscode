        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Unable to get upgradeable socket handle");
        return ap_pass_brigade(f->next, bb);
    }


    /* Send the interim 101 response. */
    upgradebb = apr_brigade_create(r->pool, f->c->bucket_alloc);

    ap_fputstrs(f->next, upgradebb, SWITCH_STATUS_LINE, CRLF,
                UPGRADE_HEADER, CRLF, CONNECTION_HEADER, CRLF, CRLF, NULL);

    b = apr_bucket_flush_create(f->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(upgradebb, b);

    rv = ap_pass_brigade(f->next, upgradebb);
    if (rv) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "could not send interim 101 Upgrade response");
        return AP_FILTER_ERROR;
    }

    key = get_port_key(r->connection);

    if (csd && key) {
        int sockdes;
