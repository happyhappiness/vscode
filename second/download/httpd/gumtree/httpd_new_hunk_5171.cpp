
        status = ap_get_brigade(r->input_filters, input_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            conn_rec *c = r->connection;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02610)
                          "read request body failed to %pI (%s)"
                          " from %s (%s)", p_conn->addr,
                          p_conn->hostname ? p_conn->hostname: "",
                          c->client_ip, c->remote_host ? c->remote_host: "");
            return HTTP_BAD_REQUEST;
        }
    }

    if (bytes_spooled || force_cl) {
        add_cl(p, bucket_alloc, header_brigade, apr_off_t_toa(p, bytes_spooled));
