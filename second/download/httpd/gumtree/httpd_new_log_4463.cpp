ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(01102)
                          "error reading status line from remote "
                          "server %s:%d", backend->hostname, backend->port);