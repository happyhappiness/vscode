ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0,
                             r->server, "proxy: failed to enable ssl support "
                             "for %pI (%s)", p_conn->addr, p_conn->name);