ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
                     "proxy: connection complete to %pI (%s)",
                     p_conn->addr, p_conn->name);