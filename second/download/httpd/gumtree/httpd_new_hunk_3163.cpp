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

/* Perform a speculative (and non-blocking) read from the connection
 * filters for the given request, to determine whether there is any
 * pending data to read.  Return non-zero if there is, else zero. */
static int has_buffered_data(request_rec *r)
{
    apr_bucket_brigade *bb;
    apr_off_t len;
    apr_status_t rv;
    int result;

    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);

    rv = ap_get_brigade(r->connection->input_filters, bb, AP_MODE_SPECULATIVE,
                        APR_NONBLOCK_READ, 1);
    result = rv == APR_SUCCESS
        && apr_brigade_length(bb, 1, &len) == APR_SUCCESS
        && len > 0;

    apr_brigade_destroy(bb);

    return result;
}

/*
 *  Post Read Request Handler
 */
