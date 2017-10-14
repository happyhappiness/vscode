ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                             "proxy: AJP: cping/cpong failed to %pI (%s)",
                             worker->cp->addr,
                             worker->hostname);