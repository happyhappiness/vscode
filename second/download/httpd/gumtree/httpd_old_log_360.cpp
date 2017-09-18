ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
                         "proxy: keepalive address mismatch / connection has"
                         " changed (close old socket (%s/%s, %d/%d))", 
                         p_conn->name, backend->hostname, p_conn->port,
                         backend->port);