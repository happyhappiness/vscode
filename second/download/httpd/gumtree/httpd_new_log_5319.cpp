r(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00334)
                 "Child: Accept thread listening on %s:%d using AcceptFilter %s",
                 lr->bind_addr->hostname ? lr->bind_addr->hostname : "*",
                 lr->bind_addr->port, accf_name);