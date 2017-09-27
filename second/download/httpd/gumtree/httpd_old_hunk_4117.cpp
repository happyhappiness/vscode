
    buf = apr_pstrdup(p, "Upgrade: WebSocket" CRLF "Connection: Upgrade" CRLF CRLF);
    ap_xlate_proto_to_ascii(buf, strlen(buf));
    e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(header_brigade, e);

    if ((rv = ap_proxy_pass_brigade(c->bucket_alloc, r, conn, backconn,
                                    header_brigade, 1)) != OK)
        return rv;

    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, "setting up poll()");

    if ((rv = apr_pollset_create(&pollset, 2, p, 0)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02443)
                      "error apr_pollset_create()");
        return HTTP_INTERNAL_SERVER_ERROR;
