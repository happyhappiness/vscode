static int send_request_body(request_rec *r, proxy_conn_rec *conn)
{
    if (ap_should_client_block(r)) {
        char *buf = apr_palloc(r->pool, AP_IOBUFSIZE);
        int status;
        apr_size_t readlen;

        readlen = ap_get_client_block(r, buf, AP_IOBUFSIZE);
        while (readlen > 0) {
            status = sendall(conn, buf, readlen, r);
            if (status != OK) {
                return HTTP_SERVICE_UNAVAILABLE;
            }
            readlen = ap_get_client_block(r, buf, AP_IOBUFSIZE);
        }
        if (readlen == -1) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "proxy: " PROXY_FUNCTION ": receiving request body "
                          "failed");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    return OK;
}