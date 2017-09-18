ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
                     "proxy: checking remote machine [%s] against [%s]", uri_addr->hostname, npent[j].name);