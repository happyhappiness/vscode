ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                        "Hostname %s provided via SNI and hostname %s provided"
                        " via HTTP are different", servername, host);