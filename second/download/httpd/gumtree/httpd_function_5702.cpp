static apr_status_t upgrade_connection(request_rec *r)
{
    struct conn_rec *conn = r->connection;
    apr_bucket_brigade *bb;
    SSLConnRec *sslconn;
    apr_status_t rv;
    SSL *ssl;

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

    if (rv) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02029)
                      "failed to send 101 interim response for connection "
                      "upgrade");
        return rv;
    }

    ssl_init_ssl_connection(conn, r);

    sslconn = myConnConfig(conn);
    ssl = sslconn->ssl;

    /* Perform initial SSL handshake. */
    SSL_set_accept_state(ssl);
    SSL_do_handshake(ssl);

    if (SSL_get_state(ssl) != SSL_ST_OK) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02030)
                      "TLS upgrade handshake failed: not accepted by client!?");

        return APR_ECONNABORTED;
    }

    return APR_SUCCESS;
}