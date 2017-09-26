        if (status != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                         "proxy: processing prefetched request body failed"
                         " to %pI (%s) from %s (%s)",
                         p_conn->addr, p_conn->hostname ? p_conn->hostname: "",
                         c->remote_ip, c->remote_host ? c->remote_host: "");
            return status;
        }

    /* Ensure we don't hit a wall where we have a buffer too small
     * for ap_get_brigade's filters to fetch us another bucket,
     * surrender once we hit 80 bytes less than MAX_MEM_SPOOL
     * (an arbitrary value.)
