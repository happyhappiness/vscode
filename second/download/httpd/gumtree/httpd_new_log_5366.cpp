ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02032)
                             "Hostname %s provided via SNI and hostname %s provided"
                             " via HTTP have no compatible SSL setup",
                             servername, r->hostname);