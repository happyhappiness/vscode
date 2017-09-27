
        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            conn_rec *c = r->connection;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02608)
                          "read request body failed to %pI (%s)"
                          " from %s (%s)", p_conn->addr,
                          p_conn->hostname ? p_conn->hostname: "",
                          c->client_ip, c->remote_host ? c->remote_host: "");
            return HTTP_BAD_REQUEST;
        }
    }

    if (header_brigade) {
        /* we never sent the header brigade because there was no request body;
