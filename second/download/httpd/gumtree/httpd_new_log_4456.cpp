ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(01095)
                          "prefetch request body failed to %pI (%s)"
                          " from %s (%s)",
                          p_conn->addr, p_conn->hostname ? p_conn->hostname: "",
                          c->client_ip, c->remote_host ? c->remote_host: "");