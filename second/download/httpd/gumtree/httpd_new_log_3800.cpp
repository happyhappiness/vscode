ap_log_error(APLOG_MARK, APLOG_ERR, errno, ap_server_conf, APLOGNO(01240)
                             "Couldn't unlink unix domain socket %s",
                             sockname);