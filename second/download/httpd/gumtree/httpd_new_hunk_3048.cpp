    temp_brigade = apr_brigade_create(p, bucket_alloc);
    do {
        status = ap_get_brigade(r->input_filters, temp_brigade,
                                AP_MODE_READBYTES, APR_BLOCK_READ,
                                MAX_MEM_SPOOL - bytes_read);
        if (status != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01095)
                          "prefetch request body failed to %pI (%s)"
                          " from %s (%s)",
                          p_conn->addr, p_conn->hostname ? p_conn->hostname: "",
                          c->client_ip, c->remote_host ? c->remote_host: "");
            return HTTP_BAD_REQUEST;
        }

        apr_brigade_length(temp_brigade, 1, &bytes);
        bytes_read += bytes;

