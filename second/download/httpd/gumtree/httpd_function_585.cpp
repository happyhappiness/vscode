static apr_status_t ssl_io_filter_Upgrade(ap_filter_t *f,
                                         apr_bucket_brigade *bb)

{
    const char *upgrade;
    apr_bucket_brigade *upgradebb;
    request_rec *r = f->r;
    apr_socket_t *csd = NULL;
    char *key;
    int ret;
    secsocket_data *csd_data;
    apr_bucket *b;
    apr_status_t rv;

    /* Just remove the filter, if it doesn't work the first time, it won't
     * work at all for this request.
     */
    ap_remove_output_filter(f);

    /* No need to ensure that this is a server with optional SSL, the filter
     * is only inserted if that is true.
     */

    upgrade = apr_table_get(r->headers_in, "Upgrade");
    if (upgrade == NULL
        || strcmp(ap_getword(r->pool, &upgrade, ','), "TLS/1.0")) {
            /* "Upgrade: TLS/1.0, ..." header not found, don't do Upgrade */
        return ap_pass_brigade(f->next, bb);
    }

    apr_table_unset(r->headers_out, "Upgrade");

    if (r) {
        csd_data = (secsocket_data*)ap_get_module_config(r->connection->conn_config, &nwssl_module);
        csd = csd_data->csd;
    }
    else {
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
        apr_os_sock_get(&sockdes, csd);


        ret = SSLize_Socket(sockdes, key, r);
        if (!ret) {
            csd_data->is_secure = 1;
        }
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Upgradeable socket handle not found");
        return AP_FILTER_ERROR;
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "Awaiting re-negotiation handshake");

    /* Now that we have initialized the ssl connection which added the ssl_io_filter,
       pass the brigade off to the connection based output filters so that the
       request can complete encrypted */
    return ap_pass_brigade(f->c->output_filters, bb);
}