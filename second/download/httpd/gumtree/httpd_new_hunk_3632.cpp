
    if (old_cl_val && old_te_val) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01094)
                      "client %s (%s) requested Transfer-Encoding "
                      "chunked body with Content-Length (C-L ignored)",
                      c->client_ip, c->remote_host ? c->remote_host: "");
        old_cl_val = NULL;
        origin->keepalive = AP_CONN_CLOSE;
        p_conn->close = 1;
    }

    /* Prefetch MAX_MEM_SPOOL bytes
