static apr_status_t ssl_io_filter_Upgrade(ap_filter_t *f,
                                         apr_bucket_brigade *bb)

{
#define SWITCH_STATUS_LINE "HTTP/1.1 101 Switching Protocols"
#define UPGRADE_HEADER "Upgrade: TLS/1.0, HTTP/1.1"
#define CONNECTION_HEADER "Connection: Upgrade"
    const char *upgrade;
    const char *connection;
    apr_bucket_brigade *upgradebb;
    request_rec *r = f->r;
    apr_socket_t *csd = NULL;
    char *key;
    unicode_t keyFileName[512];
    int ret;
    char *token_string;
    char *token;
    char *token_state;

    /* Just remove the filter, if it doesn't work the first time, it won't
     * work at all for this request.
     */
    ap_remove_output_filter(f);

    /* No need to ensure that this is a server with optional SSL, the filter
     * is only inserted if that is true.
     */

    upgrade = apr_table_get(r->headers_in, "Upgrade");
    if (upgrade == NULL) {
        return ap_pass_brigade(f->next, bb);
    }
    token_string = apr_pstrdup(r->pool,upgrade);
    token = apr_strtok(token_string,", ",&token_state);
    while (token && strcmp(token,"TLS/1.0")) {
        apr_strtok(NULL,", ",&token_state);
    }
    // "Upgrade: TLS/1.0" header not found, don't do Upgrade
    if (!token) {
        return ap_pass_brigade(f->next, bb);
    }

    connection = apr_table_get(r->headers_in, "Connection");
    token_string = apr_pstrdup(r->pool,connection);
    token = apr_strtok(token_string,",",&token_state);
    while (token && strcmp(token,"Upgrade")) {
        apr_strtok(NULL,",",&token_state);
    }
    // "Connection: Upgrade" header not found, don't do Upgrade
    if (!token) {
        return ap_pass_brigade(f->next, bb);
    }

    apr_table_unset(r->headers_out, "Upgrade");

    if (r) {
        csd = (apr_socket_t*)ap_get_module_config(r->connection->conn_config, &nwssl_module);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Unable to get upgradeable socket handle");
        return ap_pass_brigade(f->next, bb);
    }


    if (r->method_number == M_OPTIONS) {
        apr_bucket *b = NULL;
        /* This is a mandatory SSL upgrade. */

        upgradebb = apr_brigade_create(r->pool, f->c->bucket_alloc);

        ap_fputstrs(f->next, upgradebb, SWITCH_STATUS_LINE, CRLF,
                    UPGRADE_HEADER, CRLF, CONNECTION_HEADER, CRLF, CRLF, NULL);

        b = apr_bucket_flush_create(f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(upgradebb, b);
        ap_pass_brigade(f->next, upgradebb);
    }
    else {
        /* This is optional, and should be configurable, for now don't bother
         * doing anything.
         */
        return ap_pass_brigade(f->next, bb);
    }

    key = get_port_key(r->connection);
    
    if (csd && key) {
        int sockdes;
        apr_os_sock_get(&sockdes, csd);


        ret = SSLize_Socket(sockdes, key, r);
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Upgradeable socket handle not found");
        return ap_pass_brigade(f->next, bb);
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "Awaiting re-negotiation handshake");

    return ap_pass_brigade(f->next, bb);
}