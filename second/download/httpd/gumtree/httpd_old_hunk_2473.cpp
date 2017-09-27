
    b = apr_bucket_flush_create(f->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(upgradebb, b);

    rv = ap_pass_brigade(f->next, upgradebb);
    if (rv) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "could not send interim 101 Upgrade response");
        return AP_FILTER_ERROR;
    }

    key = get_port_key(r->connection);

