ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: pass request body failed to %pI (%s)"
                     " from %s (%s)",
                     p_conn->addr,
                     p_conn->hostname ? p_conn->hostname: "",
                     c->remote_ip,
                     c->remote_host ? c->remote_host: "");