ap_log_error(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, r->server,
                         "proxy: connect to remote machine %s blocked: name %s matched", uri_addr->hostname, npent[j].name);