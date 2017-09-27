            return rc;
        }
    }
    return OK;
}

static
apr_status_t ap_proxy_http_request(apr_pool_t *p, request_rec *r,
                                   proxy_http_conn_t *p_conn, conn_rec *origin, 
                                   proxy_server_conf *conf,
                                   apr_uri_t *uri,
                                   char *url, apr_bucket_brigade *bb,
                                   char *server_portstr) {
    conn_rec *c = r->connection;
    char *buf;
    apr_bucket *e;
    const apr_array_header_t *headers_in_array;
    const apr_table_entry_t *headers_in;
    int counter, seen_eos;
    apr_status_t status;

    /*
     * Send the HTTP/1.1 request to the remote server
     */

    /* strip connection listed hop-by-hop headers from the request */
    /* even though in theory a connection: close coming from the client
     * should not affect the connection to the server, it's unlikely
     * that subsequent client requests will hit this thread/process, so
     * we cancel server keepalive if the client does.
     */
    p_conn->close += ap_proxy_liststr(apr_table_get(r->headers_in,
                                                     "Connection"), "close");
    /* sub-requests never use keepalives */
    if (r->main) {
        p_conn->close++;
    }

    ap_proxy_clear_connection(p, r->headers_in);
    if (p_conn->close) {
        apr_table_setn(r->headers_in, "Connection", "close");
        origin->keepalive = AP_CONN_CLOSE;
    }

    if ( apr_table_get(r->subprocess_env,"force-proxy-request-1.0")) {
        buf = apr_pstrcat(p, r->method, " ", url, " HTTP/1.0" CRLF, NULL);
    } else {
        buf = apr_pstrcat(p, r->method, " ", url, " HTTP/1.1" CRLF, NULL);
    }
    if ( apr_table_get(r->subprocess_env,"proxy-nokeepalive")) {
        apr_table_unset(r->headers_in, "Connection");
        origin->keepalive = AP_CONN_CLOSE;
    }
    ap_xlate_proto_to_ascii(buf, strlen(buf));
    e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);
    if ( conf->preserve_host == 0 ) {
        if (uri->port_str && uri->port != DEFAULT_HTTP_PORT) {
            buf = apr_pstrcat(p, "Host: ", uri->hostname, ":", uri->port_str, CRLF,
                            NULL);
        } else {
            buf = apr_pstrcat(p, "Host: ", uri->hostname, CRLF, NULL);
        }
    } 
    else {
        /* don't want to use r->hostname, as the incoming header might have a 
